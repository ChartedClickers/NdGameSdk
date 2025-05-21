#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/sdkstringid.hpp"
#include "NdGameSdk/database/database.hpp"
#include "NdGameSdk/sidbase/sidbase.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/common/common-game-init.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#include <Utility/helper.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/ScriptManagerGlobals.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ScriptManagerGlobals.hpp>
#endif

#include "script-manager-eval.hpp"

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::common;
using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::ndlib::script {

	class ScriptManagerGlobals;
	DEFINE_DMENU_ItemSelection(ScriptCFuncDebugMode, Execute, Editor);
	DEFINE_DMENU_ItemSelection(ScriptCFuncTypeOf, None, Bool, Int, Float, String, CFuncValue);

	class ScriptManager : public ISdkComponent {
	public:
		ScriptManager();

		SdkEvent<> e_ScriptManagerInitialized{true};
		SDK_DEPENDENCIES(CommonGame, NdDevMenu, Memory);

		NdGameSdk_API ScriptCFunc* LookupCFunc(StringId64 Hash);
		template<typename... Args>
		ScriptValue InvokeCFunc(ScriptCFunc* func, Args&&... args) {
			std::array<ScriptValue, sizeof...(Args)> argv{ ScriptValue{std::forward<Args>(args)}... };

			ScriptValue ret{};
			func->CallScriptCFunc(argv.data(), static_cast<uint32_t>(argv.size()), &ret, 0);
			return ret;
		}

		static DMENU::ItemSubmenu* CreateScriptManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);

	private:
		void Initialize() override;
		void Awake() override;

		bool RefreshScriptCFuncInfo(bool UpdateSidBase);
		ScriptCFuncInfo* FindScriptCFuncByInput(const char* input);

		static void ScriptManagerInitialized(SafetyHookContext& ctx);
		static bool TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);

		/*ScriptCFuncDebugMenu*/
		struct ScriptCFuncDebugMenuProperties {
			struct ScriptCFuncEditor {
				char DescriptionBuf[256]{};
				struct Args {
					char Description[256]{};
					char Name[128]{};
					ScriptCFuncInfo::TypeOf type{ ScriptCFuncInfo::TypeOf::None };
				};
				int NumArgs{};
				std::vector<Args> EditedArgs;
			};

			bool showAllScriptCFuncs{};
			bool UpdateSidBase{};
			char ScriptCFuncInputText[0x20]{"Enter..."};
			ScriptCFuncDebugMode ScriptCFuncDebugMode{ ScriptCFuncDebugMode::Execute };
			ScriptCFuncInfo* ScriptCFuncInfo{nullptr};
			std::unique_ptr<ScriptCFuncEditor> CFuncEditor;
		};
		template<typename CompT>
		static uint64_t OnExecuteRebuild(CompT& item,
			DMENU::Message msg,
			int32_t data) {
			auto* mgr = Instance<ScriptManager>();
			auto* menu = mgr->m_NdDevMenu;

			auto ret = menu->DecimalCallBack(item, msg, data);
			if (msg == DMENU::Message::OnExecute) {
				menu->RebuildMenuFromComponent(
					item.ParentComponent<DMENU::Menu>(),
					&item,
					{ &WrapScriptCFuncExecutorMenu },
					HeapArena_Source,
					&mgr->m_ScriptCFuncDebugMenuProperties,
					true
				);
			}
			return ret;
		}
		static bool WrapScriptCFuncDebugMenu(DMENU::Menu* pMenu, ScriptCFuncDebugMenuProperties* pProperties);
		static bool WrapScriptCFuncExecutorMenu(DMENU::Menu* pMenu, ScriptCFuncDebugMenuProperties* pProperties, bool pSwitchMode = false);
		static void SyncCFuncEditorBuffers(ScriptCFuncInfo& info, ScriptCFuncDebugMenuProperties::ScriptCFuncEditor& editor, bool toEditor);
		static bool OnUpdateScriptCFuncDebugMenu(DMENU::ItemSubmenu& pSubMenu, DMENU::Message pMessage);

		DMENU::KeyBoard* m_ScriptCFuncInput{ nullptr };
		DMENU::Menu* m_ScriptCFuncDebugMenu{ nullptr };
		DMENU::Menu* m_ScriptCFuncDebugExecuteMenu{ nullptr };
		ScriptCFuncDebugMenuProperties m_ScriptCFuncDebugMenuProperties{};
		bool m_CFuncDebugRefresh = false;
		bool m_CFuncDebugRefreshData = false;
		std::string m_NativeTableEntriesText{ "// Native table contains {:d} entries" };
		std::map<StringId64, ScriptCFuncInfo> m_ScriptCFuncs{};
		

		Memory* m_Memory;
		CommonGame* m_CommonGame;
		NdDevMenu* m_NdDevMenu;

		MidHook m_ScriptManagerInitHook{};

		static std::string s_DataBaseFile;

		/*Extern variables*/
		ScriptManagerGlobals* g_ScriptManagerGlobals{};
	};

    class NdGameSdk_API ScriptManagerGlobals : public ISdkRegenny<regenny::shared::ndlib::script::ScriptManagerGlobals> {
    public:
		using ScriptCFuncMap = regenny::shared::ndlib::script::ScriptManagerGlobals::ScriptCFuncMap;
        struct NativeFuncEntry {
			StringId64 hash;
            void* Funct;
        };

        ScriptCFuncMap* GetNativeMap();
		std::vector<NativeFuncEntry> DumpNativeFunctions();
    };

#pragma region JsonSerialize
	inline void to_json(nlohmann::json& j, const std::map<StringId64, ScriptCFuncInfo>& m) {
		for (auto& [k, v] : m) {
			j[std::to_string(k)] = v;
		}
	}

	inline void from_json(const nlohmann::json& j, std::map<StringId64, ScriptCFuncInfo>& m) {
		m.clear();
		for (auto& [k, v] : j.items()) {
			m[static_cast<StringId64>(std::stoull(k))] = v.get<ScriptCFuncInfo>();
		} 
	}
#pragma endregion

#if defined(T2R)
	static_assert(sizeof(ScriptManagerGlobals) == 0x7a0, "Size of ScriptManagerGlobals is not correct.");
#elif defined(T1X)
	static_assert(sizeof(ScriptManagerGlobals) == 0x33b0, "Size of ScriptManagerGlobals is not correct.");
#endif
}