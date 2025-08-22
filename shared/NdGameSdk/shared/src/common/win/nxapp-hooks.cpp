#if defined(T2R)	
#include "nxapp-hooks.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/common/common-game-init.hpp>

namespace NdGameSdk::common::win {

	NxAppHooks::NxAppHooks() : ISdkSubComponent(TOSTRING(NxAppHooks)) {}

	void OpenAndRedirectStdIO_CC();

	void NxAppHooks::Init() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::CommonGame_NxAppHooks_Init1of2;
			auto Init1of2 = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::CommonGame_NxAppHooks_Init1of2), findpattern.offset);
			
			findpattern = Patterns::CommonGame_NxAppHooks_NxApp_Init;
			auto NxAppInit = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::CommonGame_NxAppHooks_NxApp_Init), findpattern.offset);

			findpattern = Patterns::CommonGame_NxAppHooks_NxApp;
			m_gNxAppSlot = (uint8_t*)Utility::ReadLEA32(module, 
				findpattern.pattern, wstr(Patterns::CommonGame_NxAppHooks_NxApp), findpattern.offset, 3, 8 );

			if (!Init1of2 ||
				!NxAppInit ||
				!m_gNxAppSlot) {
				throw SdkComponentEx{ std::format("Failed to find {}:: NxAppHooks addresses!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_NxAppInitHook = Utility::MakeSafetyHookInline(NxAppInit, NxAppHooks::NxAppInit,
				wstr(Patterns::CommonGame_NxAppHooks_NxApp_Init), wstr(NxApp::Init));

			m_Init1of2Hook = Utility::MakeSafetyHookInline(Init1of2, NxAppHooks::Init1of2,
				wstr(Patterns::CommonGame_NxAppHooks_Init1of2), wstr(Init1of2));

			if (!m_NxAppInitHook ||
				!m_Init1of2Hook) {
				throw SdkComponentEx{ "Failed to create hooks!", 
					SdkComponentEx::ErrorCode::PatchFailed };
			}

		});
	}

	NxApp* NxAppHooks::GetNxApp() {
		always_assert(m_gNxAppSlot == nullptr, "g_NxApp slot not resolved");
		return *reinterpret_cast<NxApp* volatile*>(m_gNxAppSlot);
	}

	bool __fastcall NxAppHooks::NxAppInit(void* pAllocator) {
		NxAppHooks* pNxAppHooks = GetSharedComponents()->
			GetComponent<CommonGame>()->GetSubComponent<NxAppHooks>();

		bool result = pNxAppHooks->m_NxAppInitHook.thiscall<bool>(pAllocator);

		if (result) {

			NxApp::NixxesLogger* pLogger = pNxAppHooks->GetNxApp()->GetLogger();
			if (pLogger) {
				auto** vft = reinterpret_cast<void**>(pLogger->Get()->vftable);

				pNxAppHooks->m_OpenAndRedirectStdIOHook = Utility::MakeFunctionHook(
					vft[NxApp::NixxesLogger::kIdx_OpenAndRedirectStdIO],
					(void*)OpenAndRedirectStdIO_CC,
					wstr(Patterns::CommonGame_NxAppHooks_OpenAndRedirectStdIO));

				if (!pNxAppHooks->m_OpenAndRedirectStdIOHook) {
					spdlog::warn("Failed to patch {:s}! Logs may not work!", TOSTRING(vft[NxApp::NixxesLogger::kIdx_OpenAndRedirectStdIO]));
				}
			}
			else {
				spdlog::error("NxApp::NixxesLogger is null! Logs may not work!");
			}
		
		}

		pNxAppHooks->InvokeSdkEvent(pNxAppHooks->e_NxAppInitialized, result ? pNxAppHooks->GetNxApp() : nullptr, result);
		return result;
	}

	bool __fastcall NxAppHooks::Init1of2() {
		NxAppHooks* pNxAppHooks = GetSharedComponents()->
			GetComponent<CommonGame>()->GetSubComponent<NxAppHooks>();

		bool result = pNxAppHooks->m_Init1of2Hook.thiscall<bool>();
		return result;
	}

	NxApp::NixxesLogger* NxApp::GetLogger() const {
		return reinterpret_cast<NixxesLogger*>(this->Get()->m_logger);
	}

	void __attribute__((naked)) OpenAndRedirectStdIO_CC() {
		__asm {
			push rbx;
			mov al, 0x1;
			pop rbx;
			ret;
		}
	}
}
#endif