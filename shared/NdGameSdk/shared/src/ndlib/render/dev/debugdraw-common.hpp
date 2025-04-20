#pragma once

#if defined(T2R)

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "NdGameSdk/components/SdkModule.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#include <NdGameSdk/shared/src/common/common-game-init.hpp>

#include "../window-context.hpp"
#include "../frame-params.hpp"
#include "../util/text.hpp"

using namespace NdGameSdk::common;
using namespace NdGameSdk::ndlib::render;
using namespace NdGameSdk::ndlib::render::util;

namespace NdGameSdk::ndlib::render::dev {

	class DebugDrawCommon : public ISdkComponent {
	public:
		DebugDrawCommon();
		~DebugDrawCommon();

		RenderFrameParams m_RenderFrameParams{};
		Text m_Text{};

	private:
		void Awake() override;
		void Initialize() override;

		void OnGameInitialized(bool successful);

		static void DebugDraw(SafetyHookContext& ctx);

		MidHook m_DebugDrawHook{};

		shared_ptr<CommonGame> m_CommonGame;
		static DebugDrawCommon* s_DebugDraw;

		friend class ISdkModule;
	};

}

#endif