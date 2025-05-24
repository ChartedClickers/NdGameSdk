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
				case ScriptCFuncInfo::TypeOf::String: {
                    auto str = reinterpret_cast<const char*>(arg.Data);
                    if (str && *str) {
                    u = reinterpret_cast<uint64_t>(str);
                    }
				} break;
				case TypeOf::StringId:
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

	InlineHook ScriptCFunc::InlinePatchCfunc(void* target_jmp, const wchar_t* source_name, const wchar_t* hook_name) {
		InlineHook CfuncHook =
			Utility::MakeSafetyHookInline(this->GetFunc(), target_jmp, source_name, hook_name);

		if (CfuncHook) {
			spdlog::warn(
				"InlineHook ScriptCFunc: {:#x} -> {:#x} ({:#x} -> {:#x}) | Hook target address: {:#x}",
				reinterpret_cast<uintptr_t>(this->GetFunc()),
				reinterpret_cast<uintptr_t>(target_jmp),
				reinterpret_cast<uintptr_t>(source_name),
				reinterpret_cast<uintptr_t>(hook_name),
				reinterpret_cast<uintptr_t>(CfuncHook.target_address())
			);
			return CfuncHook;
		}

		spdlog::error(
			"Failed to InlineHook ScriptCFunc: {:#x} -> {:#x} ({:#x} -> {:#x})",
			reinterpret_cast<uintptr_t>(this->GetFunc()),
			reinterpret_cast<uintptr_t>(target_jmp),
			reinterpret_cast<uintptr_t>(source_name),
			reinterpret_cast<uintptr_t>(hook_name)
		);
		return {};
	}

	MidHook ScriptCFunc::PatchCfunc(MidHookFn target_jmp, const wchar_t* source_name, const wchar_t* hook_name) {
		MidHook CfuncHook =
			Utility::MakeMidHook(this->GetFunc(), target_jmp, source_name, hook_name);

		if (CfuncHook) {
			spdlog::warn(
				"MidHook ScriptCFunc: {:#x} -> {:#x} ({:#x} -> {:#x}) | Hook target address: {:#x}",
				reinterpret_cast<uintptr_t>(this->GetFunc()),
				reinterpret_cast<uintptr_t>(target_jmp),
				reinterpret_cast<uintptr_t>(source_name),
				reinterpret_cast<uintptr_t>(hook_name),
				reinterpret_cast<uintptr_t>(CfuncHook.target_address())
			);
			return CfuncHook;
		}

		spdlog::error(
			"Failed to MidHook ScriptCFunc: {:#x} -> {:#x} ({:#x} -> {:#x})",
			reinterpret_cast<uintptr_t>(this->GetFunc()),
			reinterpret_cast<uintptr_t>(target_jmp),
			reinterpret_cast<uintptr_t>(source_name),
			reinterpret_cast<uintptr_t>(hook_name)
		);
		return {};
	}

	FunctionHook::Ptr ScriptCFunc::MakeFunctionHook(void* target_jmp, const wchar_t* hook_name) {
		FunctionHook::Ptr CfuncHook =
			Utility::MakeFunctionHook(this->GetFunc(), target_jmp, hook_name);

		if (CfuncHook) {
			spdlog::warn(
				"FunctionHook ScriptCFunc: {:#x} -> {:#x} ({:#x}) | Hook target address: {:#x}",
				reinterpret_cast<uintptr_t>(this->GetFunc()),
				reinterpret_cast<uintptr_t>(target_jmp),
				reinterpret_cast<uintptr_t>(hook_name),
				*CfuncHook->GetTarget()
			);
			return CfuncHook;
		}

		spdlog::error(
			"Failed to FunctionHook ScriptCFunc: {:#x} -> {:#x} ({:#x})",
			reinterpret_cast<uintptr_t>(this->GetFunc()),
			reinterpret_cast<uintptr_t>(target_jmp),
			reinterpret_cast<uintptr_t>(hook_name)
		);
		return {};
	}


	INIT_FUNCTION_PTR(ScriptManager_LookupSymbol);
	INIT_FUNCTION_PTR(ScriptManager_LookupInModule);
	INIT_FUNCTION_PTR(ScriptManager_BindValue);
	INIT_FUNCTION_PTR(ScriptManager_UnbindValue);
}