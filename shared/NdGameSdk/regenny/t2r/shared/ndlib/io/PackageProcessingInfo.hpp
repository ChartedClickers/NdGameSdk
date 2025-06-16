#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "Package.hpp"
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct PackageProcessingInfo {
    enum LoadingStatus : uint32_t {
        LoadingPackageStatusUnused = 0,
        LoadingPackageStatusError = 1,
        LoadingPackageStatusInvalid = 2,
        LoadingPackageStatusWanted = 3,
        LoadingPackageStatusOpenFile = 4,
        LoadingPackageStatusLoadingPakHeader = 5,
        LoadingPackageStatusLoadingHeader = 6,
        LoadingPackageStatusLoadingPages = 7,
        LoadingPackageStatusLoadingVram = 8,
        LoadingPackageStatusWaitingForVramPages = 9,
        LoadingPackageStatusDataIsLoaded = 10,
        LoadingPackageStatusWaitingForVramProcessing = 11,
        LoadingPackageStatusDoingLogin = 12,
        LoadingPackageStatusFinalizing = 13,
        LoadingPackageStatusLoaded = 14,
        LoadingPackageStatusWaitingForLogout = 15,
        LoadingPackageStatusDoingLogout = 16,
        LoadingPackageStatusWaitingForUnload = 17,
        LoadingPackageStatusFailedOptionalFile = 18,
    };

    regenny::shared::ndlib::io::Package* m_package; // 0x0
    LoadingStatus m_status; // 0x8
    private: char pad_c[0x204]; public:
    uint64_t m_NumAsyncReadOps; // 0x210
    uint64_t m_handle; // 0x218
    private: char pad_220[0x10]; public:
    uint64_t m_ChunkSize; // 0x230
    private: char pad_238[0x7e0]; public:
    uint64_t m_fielda18; // 0xa18
    private: char pad_a20[0x18]; public:
    regenny::shared::ndlib::io::Package::PakHeader m_pakHdr; // 0xa38
}; // Size: 0xad0
#pragma pack(pop)
}
