#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
enum FhOpenFlags : uint32_t {
    FHOF_ALLOW_CREATE = 64,
    FHOF_TRUNCATE = 512,
    FHOF_MODE_04 = 1024,
    FHOF_DIRECT_IO = 4096,
};
#pragma pack(pop)
}
