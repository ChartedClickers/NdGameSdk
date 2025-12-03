#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>
#include <functional>
#include <dstorage.h>
#include <Windows.h>

namespace NdGameSdk::ndlib::io { 
    
#if defined(T2R)

    class StorageCore;

    namespace PSARC {

        struct iReader {
            virtual ~iReader() = default;
            virtual bool Read(uint64_t ofs, void* dst, size_t sz) = 0;
        };

        class Win32Reader final : public iReader {
        public:
            explicit Win32Reader(HANDLE h) : m_h(h) {}
            bool Read(uint64_t ofs, void* dst, size_t sz) override;
        private:
            HANDLE m_h{};
        };

        class DSReader final : public iReader {
        public:
            DSReader(StorageCore* sc, IDStorageFile* file) : m_StorageCore(sc), m_file(file) {}
            bool Read(uint64_t ofs, void* dst, size_t sz) override;
        private:
            StorageCore* m_StorageCore{};
            IDStorageFile* m_file{};
        };

        // Lightweight wrapper around a callable read and an owned payload to keep dependencies alive.
        class DSARStream final : public iReader {
        public:
            using ReadFn = std::function<bool(uint64_t, void*, size_t)>;
            DSARStream(std::shared_ptr<void> keepAlive, ReadFn fn)
                : m_keepAlive(std::move(keepAlive)), m_read(std::move(fn)) {}
            bool Read(uint64_t ofs, void* dst, size_t sz) override { return m_read(ofs, dst, sz); }
        private:
            std::shared_ptr<void> m_keepAlive{};
            ReadFn m_read{};
        };

        // Adapts a base reader into a PSARC-capable reader.
        // If the source is DSAR, returns a DSARStream; if PSAR, returns the base.
        std::unique_ptr<iReader> AsPsarcReader(std::unique_ptr<iReader> base);

    } 

#endif

}
