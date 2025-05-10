#include "script-manager-eval.hpp"

#include <NdGameSdk/shared/src/gamelib/statescript/ss-context.hpp>

using namespace NdGameSdk::gamelib::statescript;

namespace NdGameSdk::ndlib::script {

	ScriptValue ScriptCFuncInfo::makeScriptArgs() {
		ScriptValue sv{};
		if (auto raw = sv.Get()) {
			const size_t max = std::size(raw->val);
			size_t n = (std::min)(Args.size(), max);
			for (size_t i = 0; i < n; ++i) {
				const auto& arg = Args[i];
				uint64_t u = 0;
				switch (arg.Type) {
				case ScriptCFuncInfo::TypeOf::Bool:
					u = *reinterpret_cast<const bool*>(arg.Data);
					break;
				case ScriptCFuncInfo::TypeOf::Int:
					u = static_cast<uint64_t>(*reinterpret_cast<const uint16_t*>(arg.Data));
					break;
				case ScriptCFuncInfo::TypeOf::Float: {
					float f = *reinterpret_cast<const float*>(arg.Data);
					std::memcpy(&u, &f, sizeof(f));
					break;
				}
				case ScriptCFuncInfo::TypeOf::CFuncValue: {
					u = arg.Data[0x0];
				} break;
				case TypeOf::String:
				default: {
					auto str = reinterpret_cast<const char*>(arg.Data);
					if (str && *str) {
						u = ParseStringToStringId(str);
					}
				} break;
				}
				raw->val[i] = u;
			}
		}
		return sv;
	}

	ScriptValue::ScriptValue(std::initializer_list<uint64_t> init) : ScriptValue() {
		if (auto self = this->Get()) {
			size_t n = (std::min)(init.size(), std::size(self->val));
			auto it = init.begin();
			for (size_t i = 0; i < n; ++i, ++it) {
				self->val[i] = *it;
			}
		}
	}

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

	void ScriptCFunc::CallScriptCFunc(ScriptValue args, int numArgs, ScriptValue* return_)  {
		auto* CFunc = this->Get();
		if (!CFunc || !CFunc->vftable) return;

		auto** table = reinterpret_cast<void***>(CFunc)[0];
		using Fn = uint64_t(__fastcall*)(
			void* /*self*/,
			regenny::shared::gamelib::state_script::ScriptCFuncContext* CFuncContext,
			uint32_t ArgsNum,
			regenny::shared::ndlib::script::ScriptValue* return_,
			uint64_t
			);

		auto CallScriptCFunc = reinterpret_cast<Fn>(table[0]);

		ScriptCFuncContext ctx{ args };
		CallScriptCFunc(CFunc, ctx.Get(), static_cast<uint32_t>(numArgs), return_->Get(), 0);
	}

	void* ScriptCFunc::GetFunc() const {
		return this->Get()->m_pFunction;
	}

	INIT_FUNCTION_PTR(ScriptManager_LookupCFunc);
}