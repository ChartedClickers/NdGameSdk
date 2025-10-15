#pragma once  

#include <NdGameSdk/shared/src/ndlib/script/script-manager-eval.hpp>

#if defined(T2R)  
#include <NdGameSdk/regenny/t2r/shared/gamelib/state_script/ScriptCFuncContext.hpp>  
#include <NdGameSdk/regenny/t2r/shared/gamelib/state_script/CFunctionStack.hpp>  
#elif defined(T1X)  
#include <NdGameSdk/regenny/t1x/shared/gamelib/state_script/ScriptCFuncContext.hpp>  
#include <NdGameSdk/regenny/t1x/shared/gamelib/state_script/CFunctionStack.hpp>  
#endif  

namespace NdGameSdk::ndlib::script {
	class ScriptValue;
}

namespace NdGameSdk::gamelib::statescript {  

class ScriptCFuncContext : public ISdkRegenny<regenny::shared::gamelib::state_script::ScriptCFuncContext>   
{ 
public:
	ScriptCFuncContext() = default;  

    ScriptCFuncContext(const NdGameSdk::ndlib::script::ScriptValue& pArgs)
    {
        auto self = this->Get();
        if (auto raw = pArgs.Get()) {
            self->m_args = *raw;
        }
    }

};  

class CFunctionStack : public ISdkRegenny<regenny::shared::gamelib::state_script::CFunctionStack> {};  

static_assert(sizeof(ScriptCFuncContext) == 0x208, "Size of ScriptCFuncContext is not correct.");
static_assert(sizeof(CFunctionStack) == 0x40, "Size of CFunctionStack is not correct.");  

}