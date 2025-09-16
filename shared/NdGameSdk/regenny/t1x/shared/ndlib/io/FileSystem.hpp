#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FileSystem {
    struct ArchiveMount {
        enum ArchiveMountFlags : uint32_t {
            Patch = 1,
            Dynamic = 2,
            Opaque = 4,
        };

        uint32_t m_fh; // 0x0
        ArchiveMountFlags m_flags; // 0x4
        void* m_pMountBuffer; // 0x8
        uint64_t m_sizeBytes; // 0x10
    }; // Size: 0x18

}; // Size: 0x0
#pragma pack(pop)
}
