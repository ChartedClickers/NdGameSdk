#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T1X)

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ScriptValue.hpp>
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ScriptCFunc.hpp>
#endif

namespace NdGameSdk::ndlib::script {

	class ScriptValue : public ISdkRegenny<regenny::shared::ndlib::script::ScriptValue> 
	{
		template <typename T>
		T* as() const {
			return (T*)this;
		}

		template <typename T>
		T val(int index) const {
			return (T)this->Get()->val[index];
		}
	};

	static_assert(sizeof(ScriptValue) == 0x80, "Size of ScriptValue is not correct.");
}

#endif