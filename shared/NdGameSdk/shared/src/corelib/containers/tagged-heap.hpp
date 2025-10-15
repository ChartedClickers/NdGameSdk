#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/TaggedHeap.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/TaggedHeap.hpp>
#endif

namespace NdGameSdk::corelib::containers {
    class NdGameSdk_API TaggedHeap : public ISdkRegenny<regenny::shared::corelib::containers::TaggedHeap> {};
}