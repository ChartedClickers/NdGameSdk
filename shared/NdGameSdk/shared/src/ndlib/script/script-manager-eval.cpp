#include "script-manager-eval.hpp"

#include <NdGameSdk/shared/src/gamelib/statescript/ss-context.hpp>

using namespace NdGameSdk::gamelib::statescript;

namespace NdGameSdk::ndlib::script {

	inline uint64_t InvokeScriptCFunc(ScriptCFunc* inst,
		regenny::shared::gamelib::state_script::ScriptCFuncContext* ctx,
		uint32_t numArgs,
		regenny::shared::ndlib::script::ScriptValue* ret,
		uint64_t arg4 = 0
	) {
		using RawCallFn = uint64_t(__thiscall*)(
			ScriptCFunc*,
			regenny::shared::gamelib::state_script::ScriptCFuncContext*,
			uint32_t,
			regenny::shared::ndlib::script::ScriptValue*,
			uint64_t
			);

		auto** table = *reinterpret_cast<void***>(inst);

		auto raw = reinterpret_cast<RawCallFn>(table[0]);

		return raw(inst, ctx, numArgs, ret, arg4);
	}

	void ScriptCFunc::CallScriptCFunc(ScriptValue args, int numArgs, ScriptValue* return_)  {
		auto* CFunc = this->Get();
		if (!CFunc || !CFunc->vftable) return;

		ScriptCFuncContext ctx { args };

		auto** table = reinterpret_cast<void***>(CFunc)[0];
		using Fn = uint64_t(__fastcall*)(
			void* /*self*/,
			regenny::shared::gamelib::state_script::ScriptCFuncContext*,
			uint32_t,
			regenny::shared::ndlib::script::ScriptValue*,
			uint64_t
			);

		/*
		 It is a dirty method for executing a virtual function. 
		 By some reason, the compiler takes the ptr address of VfTable instead of using the actual this (ScriptCFunc)
		 So we need to use the first element of the table as a function pointer. I will look into it later.
		 CFunc->vftable->CallScriptCFunc(ctx.Get(), numArgs, return_->Get(), 0);
		 00007FFE2C2FC03C  mov         rax,qword ptr [CFunc]
		 00007FFE2C2FC041  mov         rcx,qword ptr [rax] // There is the problem (Clang)
		 00007FFE2C2FC044  mov         r8d,dword ptr [numArgs]
		 00007FFE2C2FC049  mov         rax,qword ptr [rcx]
		 00007FFE2C2FC04C  xor         edx,edx
		 00007FFE2C2FC04E  mov         r9d,edx
		 00007FFE2C2FC051  mov         rdx,r9
		 00007FFE2C2FC054  mov         qword ptr [rsp+20h],0
		 00007FFE2C2FC05D  call        qword ptr [rax]
		*/

		auto CallScriptCFunc = reinterpret_cast<Fn>(table[0]);
		CallScriptCFunc(CFunc, ctx.Get(), static_cast<uint32_t>(numArgs), return_->Get(), 0);
	}

	void* ScriptCFunc::GetFunc() const {
		return this->Get()->m_pFunction;
	}

	INIT_FUNCTION_PTR(ScriptManager_LookupCFunc);
}