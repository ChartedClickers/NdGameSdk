#pragma once
#include "sdkconst.hpp"

namespace NdGameSdk::Patterns
{
    struct SdkPattern {
        const wchar_t* pattern{};
        size_t offset{};
    };
}