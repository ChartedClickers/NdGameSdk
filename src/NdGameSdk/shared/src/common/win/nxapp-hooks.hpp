#pragma once
#if defined(T2R)
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/common/win/NxApp.hpp>
#endif

using namespace Utility::memory;

namespace NdGameSdk::common::win {

	class NxAppHooks;

	class NxApp : public ISdkRegenny<regenny::shared::common::win::NxApp> {
	public:
		class NixxesLogger : public ISdkRegenny<regenny::shared::common::win::NxApp::NixxesLogger>  {
		public:

			static constexpr size_t kIdx_OpenAndRedirectStdIO = 0x10 / sizeof(void*);
			static constexpr size_t kIdx_WriteRawLine = 0x40 / sizeof(void*);
			static constexpr size_t kIdx_Logf = 0x48 / sizeof(void*);
		};

		NixxesLogger* GetLogger() const;
	};

	class NxAppHooks : public ISdkSubComponent {
	public:
		explicit NxAppHooks();

		SdkEvent<NxApp*, bool> e_NxAppInitialized{ true };

		NxApp* GetNxApp();

	private:
		void Init() override;

		/*Extern functions*/
		static bool __fastcall NxAppInit(void* pAllocator);
		static bool __fastcall Init1of2();

		/*Extern variables*/
		uint8_t* m_gNxAppSlot = nullptr;

		InlineHook m_Init1of2Hook{};
		InlineHook m_NxAppInitHook{};
		FunctionHook::Ptr m_OpenAndRedirectStdIOHook{};
	};

}
#endif