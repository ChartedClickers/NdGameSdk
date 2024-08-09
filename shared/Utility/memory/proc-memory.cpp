#include "proc-memory.hpp"
#include "Module.hpp"

#include <spdlog/spdlog.h>
#include <shared_mutex>

#pragma comment(lib,"Version.lib")

namespace Utility::memory {

    uintptr_t ReadMultiLevelPointer(uintptr_t base, const std::vector<uint32_t>& offsets)
    {
        MEMORY_BASIC_INFORMATION mbi{};
        for (auto& offset : offsets)
        {
            if (!VirtualQuery(reinterpret_cast<LPCVOID>(base), &mbi, sizeof(MEMORY_BASIC_INFORMATION)) || mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))
                return 0;

            base = *reinterpret_cast<uintptr_t*>(base) + offset;
        }

        return base;
    }

    // https://github.com/cursey/kananlib/blob/main/src/Scan.cpp#L1075 By PrayDog
    PIMAGE_RUNTIME_FUNCTION_ENTRY FindFunctionEntry(uintptr_t middle) {

        const auto module = (uintptr_t)get_module_within(middle).value_or(nullptr);

        if (module == 0 || middle == 0) { return {}; }

        const auto module_size = get_module_size((HMODULE)module).value_or(0xDEADBEEF);
        const auto module_end = module + module_size;

        const auto middle_rva = middle - module;

        // We are storing a list of ranges inside buckets, so we can quickly find the correct bucket
        // Doing this with multithreading was much slower and inefficient
        struct Bucket {
            uint32_t start_range{};
            uint32_t end_range{};
            std::vector<PIMAGE_RUNTIME_FUNCTION_ENTRY> entries{};
        };

        static std::shared_mutex bucket_mtx{};
        static std::unordered_map<uintptr_t, std::vector<Bucket>> module_buckets{};

        constexpr size_t NUM_BUCKETS = 2048;
        bool needs_insert = false;

        {
            std::shared_lock _{ bucket_mtx };

            if (auto it = module_buckets.find(module); it != module_buckets.end()) {
                if (it->second.empty()) {
                    needs_insert = true;
                }
            }
            else {
                needs_insert = true;
            }
        }

        if (needs_insert) {

            // This function abuses the fact that most non-obfuscated binaries have
            // an exception directory containing a list of function start and end addresses.
            // Get the PE header, and then the exception directory
            const auto dos_header = (PIMAGE_DOS_HEADER)module;
            const auto nt_header = (PIMAGE_NT_HEADERS)((uintptr_t)dos_header + dos_header->e_lfanew);
            const auto exception_directory = (PIMAGE_DATA_DIRECTORY)&nt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];

            // Get the exception directory RVA and size
            const auto exception_directory_rva = exception_directory->VirtualAddress;
            const auto exception_directory_size = exception_directory->Size;

            // Get the exception directory
            const auto exception_directory_ptr = (PIMAGE_RUNTIME_FUNCTION_ENTRY)((uintptr_t)dos_header + exception_directory_rva);

            // Get the number of entries in the exception directory
            const auto exception_directory_entries = exception_directory_size / sizeof(IMAGE_RUNTIME_FUNCTION_ENTRY);

            std::unique_lock _{bucket_mtx};
            auto& buckets = module_buckets[module];

            if (buckets.empty() && exception_directory_entries > 0) {
                SPDLOG_INFO("Adding {} entries for module {:x}", exception_directory_entries, module);

                std::vector<PIMAGE_RUNTIME_FUNCTION_ENTRY> sorted_entries{};
                sorted_entries.resize(exception_directory_entries);

                for (size_t i = 0; i < exception_directory_entries; ++i) {
                    sorted_entries[i] = &exception_directory_ptr[i];
                }

                std::sort(sorted_entries.begin(), sorted_entries.end(), [](const PIMAGE_RUNTIME_FUNCTION_ENTRY a, const PIMAGE_RUNTIME_FUNCTION_ENTRY b) {
                    return a->BeginAddress < b->BeginAddress;
                });

                std::erase_if(sorted_entries, [module, module_end](const PIMAGE_RUNTIME_FUNCTION_ENTRY entry) {
                    return module + entry->EndAddress > module_end || module + entry->BeginAddress > module_end || entry->EndAddress < entry->BeginAddress;
                });

                SPDLOG_INFO("Filtered and sorted entries down to {} for module {:x}", sorted_entries.size(), module);

                size_t total_added_entries = 0;

                for (auto i = 0; i < std::max<size_t>(sorted_entries.size() / NUM_BUCKETS, 1); ++i) {
                    Bucket bucket{};
                    const auto bucket_index = i * NUM_BUCKETS;
                    bucket.start_range = sorted_entries[bucket_index]->BeginAddress;
                    const auto next_index = std::min<size_t>((i + 1) * NUM_BUCKETS, sorted_entries.size());

                    uint32_t highest_end = 0;
                    for (size_t j = bucket_index; j < next_index; ++j) {
                        bucket.end_range = std::max<uint32_t>(highest_end, sorted_entries[j]->EndAddress);

                        bucket.entries.push_back(sorted_entries[j]);
                        ++total_added_entries;
                    }

                    buckets.push_back(bucket);
                }

                // Can happen, but can also happen if the number of entries is less than NUM_BUCKETS
                if (total_added_entries < sorted_entries.size()) {
                    if (buckets.empty()) {
                        SPDLOG_INFO("Adding all entries to one bucket for module {:x}", module);

                        buckets.push_back(Bucket{
                            .start_range = 0,
                            .end_range = (uint32_t)module_size,
                            .entries = {}
                        });
                    }

                    SPDLOG_INFO("Adding remaining {} entries to last bucket for module {:x}", sorted_entries.size() - total_added_entries, module);
                    // Add the remaining entries to the last bucket
                    auto& last_bucket = buckets.back();

                    for (size_t i = total_added_entries; i < sorted_entries.size(); ++i) {
                        last_bucket.entries.push_back(sorted_entries[i]);
                    }
                }
            }
        }

        // For the case where there's weird obfuscation or something
        std::vector<Bucket*> candidates{};

        {
            std::shared_lock _{ bucket_mtx };

            for (auto& bucket : module_buckets[module]) {
                // Buckets are sorted so we can break early
                if (bucket.start_range > middle_rva) {
                    break;
                }

                if (bucket.start_range <= middle_rva && middle_rva <= bucket.end_range) {
                    candidates.push_back(&bucket);
                }
            }
        }

        if (candidates.empty()) {
            return nullptr;
        }

        if (candidates.size() > 1) {
            SPDLOG_INFO("Found {} candidates for function entry", candidates.size());
        }

        PIMAGE_RUNTIME_FUNCTION_ENTRY last = nullptr;
        uint32_t nearest_distance = 0xFFFFFFFF;

        for (auto& bucket : candidates) {
            if (nearest_distance == 0) {
                break;
            }

            for (const auto& entry : bucket->entries) {
                if (nearest_distance == 0) {
                    break;
                }

                if (entry->BeginAddress == middle_rva) {
                    last = entry;
                    nearest_distance = 0;
                    break;
                }

                // Check if the middle address is within the range of the function
                if (entry->BeginAddress <= middle_rva && middle_rva <= entry->EndAddress) {
                    const auto distance = middle_rva - entry->BeginAddress;

                    if (distance < nearest_distance) {
                        nearest_distance = distance;

                        // Return the start address of the function
                        last = entry;
                    }
                }
            }
        }

    }

    optional<uintptr_t> FindFunctionStart(uintptr_t middle) {
        const auto entry = FindFunctionEntry(middle);

        if (entry != nullptr) {
            SPDLOG_INFO("Found function start for {:x} at {:x}", middle, entry->BeginAddress);
            return (uintptr_t)entry->BeginAddress + (uintptr_t)get_module_within(middle).value_or(nullptr);
        }

        return std::nullopt;
    }

    uint8_t* char_Scan(HMODULE module, const char* value)
    {
        if (!value) { return nullptr; }

        const auto data = (uint8_t*)value;
        const auto size = strlen(value) - 1;

        return scan_data<const char*>(module, data, size);
    }

    uint8_t* u32_Scan(HMODULE module, uint32_t value)
    {
        if (!value) { return nullptr; }
        return scan_value<uint32_t>(module, value);
    }

    uint8_t* u64_Scan(HMODULE module, uint64_t value)
    {
        if (!value) { return nullptr; }
        return scan_value<uint64_t>(module, value);
    }

}