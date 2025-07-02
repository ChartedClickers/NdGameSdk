#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\ndlib\io\Package.hpp"
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct DataLoading {
    struct PackageDataLoadingVTable {
        virtual bool PackageLoginResItem(regenny::shared::ndlib::io::Package* pPackage, regenny::shared::ndlib::io::Package::ResItem* pResItem) = 0;
        private: virtual void virtual_function_1() = 0; public:
        private: virtual void virtual_function_2() = 0; public:
        private: virtual void virtual_function_3() = 0; public:
        private: virtual void virtual_function_4() = 0; public:
        private: virtual void virtual_function_5() = 0; public:
        private: virtual void virtual_function_6() = 0; public:
        private: virtual void virtual_function_7() = 0; public:
        private: virtual void virtual_function_8() = 0; public:
        private: virtual void virtual_function_9() = 0; public:
        virtual void ReleaseLoadedVramPages() = 0;
    }; // Size: 0x8

    struct Config {
        uint32_t m_memsize; // 0x0
        uint32_t m_freepackageslots; // 0x4
        uint32_t m_field8; // 0x8
        uint32_t m_fieldc; // 0xc
        uint32_t m_field10; // 0x10
        uint32_t m_field14; // 0x14
        uint32_t m_field18; // 0x18
        uint32_t m_field1c; // 0x1c
    }; // Size: 0x20

}; // Size: 0x0
#pragma pack(pop)
}
