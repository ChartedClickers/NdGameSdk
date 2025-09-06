#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
enum FhOpenAccess : uint32_t {
    FHO_ACCESS_READ = 0,
    FHO_ACCESS_WRITE = 1,
    FHO_ACCESS_READWRITE = 2,
    FHO_ACCESS_RESERVED3 = 3,
};
#pragma pack(pop)
}
