#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\ndlib\io\Package.hpp"
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct DataLoading {
    struct PackageDataLoadingVTable {
        virtual bool PackageLoginResItem(regenny::shared::ndlib::io::Package* pPackage, regenny::shared::ndlib::io::Package::ResItem* pResItem) = 0;
        virtual bool FinalizePackageLogin(regenny::shared::ndlib::io::Package* pPackage, void* pContext, void* pUserData) = 0;
        virtual bool PreparePackageForLogout(regenny::shared::ndlib::io::Package* pPackage) = 0;
        virtual bool PackageLogoutResItem(regenny::shared::ndlib::io::Package* pPackage, regenny::shared::ndlib::io::Package::ResItem* pResItem) = 0;
        virtual void UnloadTextureTable(regenny::shared::ndlib::io::Package* pPackage, regenny::shared::ndlib::io::Package::PakVramItemTable* pVramTable) = 0;
        private: virtual void virtual_function_5() = 0; public:
        virtual bool RunBeginVramCmd(void* pPackageCmd, void* pCmdUserData) = 0;
        virtual bool QueueVramCmd(void* pPackageCmd, void* pCmdPayload, uint32_t arg4, uint32_t arg5) = 0;
        virtual bool ExecuteVramCmd(void* pPackageCmd) = 0;
        virtual bool BuildTextureBitmasks(regenny::shared::ndlib::io::Package* pPackage) = 0;
        virtual void ReleaseLoadedVramPages() = 0;
    }; // Size: 0x8

    struct Config {
        uint32_t m_memoryCacheSize; // 0x0
        uint32_t m_freepackageslots; // 0x4
        uint32_t m_wantLoadReserve; // 0x8
        uint32_t m_wantLoadLockedReserve; // 0xc
        uint32_t m_levelRequestReserve; // 0x10
        uint32_t m_levelDefCollectionBuckets; // 0x14
        uint32_t m_LevelDefCollectionSlots; // 0x18
        uint32_t m_MaxDependentNodeCount; // 0x1c
    }; // Size: 0x20

}; // Size: 0x0
#pragma pack(pop)
}
