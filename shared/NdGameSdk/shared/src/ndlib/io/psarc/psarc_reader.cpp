#include "psarc_reader.hpp"

#include <Windows.h>
#include <cstdint>
#include <dstorage.h>
#include <memory>

#include "../file-system-fios2.hpp"
#include "psarc_dsar.hpp"
#include "psarc.hpp"

namespace NdGameSdk::ndlib::io { 
    
#if defined(T2R)

    namespace PSARC {

        static inline uint32_t be32(const uint8_t* p);

        static bool pread_win32(HANDLE h, uint64_t offset, void* out, uint64_t len) {
            unsigned char* dst = static_cast<unsigned char*>(out);
            uint64_t remaining = len;
            while (remaining > 0) {
                DWORD toRead = remaining > 0x40000000ull ? 0x40000000u : static_cast<DWORD>(remaining);
                OVERLAPPED ov{};
                ov.Offset = static_cast<DWORD>(offset & 0xFFFFFFFFu);
                ov.OffsetHigh = static_cast<DWORD>((offset >> 32) & 0xFFFFFFFFu);
                DWORD got = 0;
                
                if (!::ReadFile(h, dst, toRead, &got, &ov)) 
                    return false;

                if (got == 0) break;
                dst += got; offset += got; remaining -= got;
            }
            return remaining == 0;
        }

        bool Win32Reader::Read(uint64_t ofs, void* dst, size_t sz) {
            if (!m_h || m_h == INVALID_HANDLE_VALUE || sz == 0) return false;
            return pread_win32(m_h, ofs, dst, static_cast<uint64_t>(sz));
        }

        bool DSReader::Read(uint64_t ofs, void* dst, size_t sz) {
            if (!m_StorageCore || !m_file || sz == 0) return false;

            IDStorageQueue* Queue = m_StorageCore->GetDirectStorageQueue();
            if (!Queue) return false;

            DSTORAGE_REQUEST req{};
            req.Options.CompressionFormat = DSTORAGE_COMPRESSION_FORMAT_NONE;
            req.Options.SourceType = DSTORAGE_REQUEST_SOURCE_FILE;
            req.Options.DestinationType = DSTORAGE_REQUEST_DESTINATION_MEMORY;
            req.Source.File.Source = m_file;
            req.Source.File.Offset = ofs;
            req.Source.File.Size = static_cast<UINT32>(sz);
            req.Destination.Memory.Buffer = dst;
            req.Destination.Memory.Size = static_cast<UINT32>(sz);

            Queue->EnqueueRequest(&req);

            HANDLE ev = ::CreateEventW(nullptr, FALSE, FALSE, nullptr);
            if (!ev) return false;

            IDStorageQueue1* q1{};
            if (SUCCEEDED(Queue->QueryInterface(__uuidof(IDStorageQueue1), reinterpret_cast<void**>(&q1))) && q1) {
                q1->EnqueueSetEvent(ev);
                q1->Release();
            }

            Queue->Submit();
            ::WaitForSingleObject(ev, INFINITE);
            ::CloseHandle(ev);
            return true;
        }

        std::unique_ptr<iReader> AsPsarcReader(std::unique_ptr<iReader> base) {
            if (!base) return {};

            uint8_t hdr[4]{};
            if (!base->Read(0, hdr, sizeof(hdr))) return {};

            const uint32_t magic = be32(hdr);
            if (magic == PSARC::MagicPSAR) 
                return base;

            if (magic == PSARC::MagicDSAR) {

                struct Holder {
                    std::unique_ptr<iReader> base;
                    DSARReader dsar;
                    explicit Holder(std::unique_ptr<iReader> b)
                        : base(std::move(b)), dsar(*base) {}
                };

                auto hold = std::make_shared<Holder>(std::move(base));
                auto fn = [hold](uint64_t ofs, void* dst, size_t sz) -> bool {
                    return hold->dsar.Read(ofs, dst, sz);
                };

                return std::unique_ptr<iReader>(new DSARStream(hold, std::move(fn)));
            }

            return {};
        }

        static inline uint32_t be32(const uint8_t* p) {
            return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | uint32_t(p[3]);
        }
    }

#endif
}
