#pragma once  
#include "NdGameSdk/components/SdkRegenny.hpp"  

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/Level.hpp>  
#endif 

namespace NdGameSdk::gamelib::level {
#if defined(T2R)
    class Level : public ISdkRegenny<regenny::shared::gamelib::level::Level>
    {
    public:

    };

    static_assert(sizeof(Level) == 0xac0, "Size of Level is not correct.");
#endif
}