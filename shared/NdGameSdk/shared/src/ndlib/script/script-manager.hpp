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

	/* Extern classes */
	class ModuleBucketMap;
	class ScriptManagerGlobals;

	DEFINE_DMENU_ItemSelection(ScriptCFuncDebugMode, Execute, Editor);
	DEFINE_DMENU_ItemSelection(ScriptCFuncTypeOf, None, Bool, Int, Float, String, CFuncValue);

	class NdGameSdk_API ScriptManager : public ISdkComponent {
	public:
		ScriptManager();

		SdkEvent<> e_ScriptManagerInitialized{true};
		SdkEvent<> e_ModuleIndexInitialized{true};

		SDK_DEPENDENCIES(CommonGame, NdDevMenu, Memory);

		ScriptCFunc* LookupCFunc(StringId64 Hash);
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

		static bool TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);

		/*Extern Functs*/
		static void ScriptManagerInitialized(SafetyHookContext& ctx);
		static void ModuleIndexInitialized(SafetyHookContext& ctx);
		static ModuleBucketMap* GetDebugModuleBucket(ScriptManagerGlobals* pScriptManagerGlobals);

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
		MidHook m_InitializeModuleIndexHook{};
		InlineHook m_GetDebugModulesHook{};

		static std::string s_DataBaseFile;

		/*Extern variables*/
		ScriptManagerGlobals* g_ScriptManagerGlobals{};

		MEMBER_FUNCTION_PTR(void, ScriptManager_ScriptModuleAdd, StringId64 module, ScriptModule* pScriptModule);
		MEMBER_FUNCTION_PTR(void, ScriptManager_ScriptModuleRemove, StringId64 module);
		MEMBER_FUNCTION_PTR(void, ScriptManager_RemoveModule, StringId64 module, bool UpdateRelocatableHeap, bool force);
		MEMBER_FUNCTION_PTR(bool, ScriptManager_AddModuleInfo, ModuleInfo module);
		MEMBER_FUNCTION_PTR(ModuleInfo*, ScriptManager_FindExportingModule, StringId64 symbol, bool restrictToModule, StringId64 module);
		MEMBER_FUNCTION_PTR(bool, ScriptManager_IsLoadModule, StringId64 module);
		MEMBER_FUNCTION_PTR(bool, ScriptManager_AddModuleRequest, StringId64 module, Memory::Context context, 
			bool pforce, bool pIncludeDependities, bool arg5, uint64_t arg6, const char* module_name);

#if defined(T2R)
		MEMBER_FUNCTION_PTR(bool, ScriptManager_ReloadModule, StringId64 module, Memory::Context context, bool loadDebug);
		MEMBER_FUNCTION_PTR(bool, ScriptManager_LoadModuleFromFile, StringId64 module, char* filePath, void* userBuffer,
			uint32_t size, Memory::Context* ContextType, bool isDebugModule, uint32_t updateAndDispatch);
#elif defined(T1X)
		MEMBER_FUNCTION_PTR(bool, ScriptManager_ReloadModule, StringId64 module, Memory::Context context);
		MEMBER_FUNCTION_PTR(bool, ScriptManager_LoadModuleFromFile, StringId64 module, bool arg2, char* filePath);
#endif

		/*
		* MEMBER_FUNCTION_PTR(void, ScriptManager_LoadStartupModule, DC::??(StartupModuleData) startup, bool Load);
		* MEMBER_FUNCTION_PTR(void, ScriptManager_InsertModuleInfoToBucket);
		* MEMBER_FUNCTION_PTR(void, ScriptManager_AddModulesToBucket, struct DC::modules::ModuleInfoArray* ModuleInfoArray, bool Islocal, bool IsDebugModule);
		*/
	};

	class NdGameSdk_API ModuleBucketMap : public ISdkRegenny<regenny::shared::ndlib::script::ModuleBucketMap> 
	{
	public:
		FixedSizeHeap* GetSymbolsHeap() const;
		FixedSizeHeap* GetModulesHeap() const;
		FixedSizeHeap* GetScriptModuleHeap() const;
		
		uint64_t MaxGlobalSymbols() const;
		uint64_t NumGlobalSymbols() const;
		uint64_t MaxModules() const;
		uint64_t NumModules() const;
		uint64_t MaxScriptModules() const;
		uint64_t NumScriptModules() const;

		ModuleInfo* ModuleHead();
		const ModuleInfo* ModuleHead() const;
		ScriptModule* ScriptModuleHead();
		const ScriptModule* ScriptModuleHead() const;

		ScriptModule* ScriptModuleTail();

		struct ModuleInfoIterator {
			ModuleInfo* cur{};
			ModuleInfo* anchor{}; // sentinel (tail)
			ModuleInfo* operator*() const { return cur; }
			ModuleInfoIterator& operator++() {
				if (!cur || cur == anchor) { cur = nullptr; return *this; }
				cur = cur->NextModule();
				if (cur == anchor) cur = nullptr;
				return *this;
			}
			bool operator!=(ModuleInfoIterator const& o) const { return cur != o.cur; }
		};

		struct ModuleInfoRange {
			ModuleInfo* first{};
			ModuleInfo* anchor{};
			std::size_t maxCnt{};
			ModuleInfoIterator begin() const { return { first,  anchor }; }
			ModuleInfoIterator end()   const { return { nullptr, anchor }; }
			std::size_t size()  const { return maxCnt; }
		};

		ModuleInfoRange Modules() {
			ModuleInfo* first = ModuleHead();
			if (!first) return { nullptr, nullptr, 0 };
			ModuleInfo* sentinel = reinterpret_cast<ModuleInfo*>(this->Get()->m_ModulesTail); // list terminator
			return { first, sentinel, GetModulesHeap()->Count() }; // guard by heap count
		}

		struct ScriptModuleIterator {
			ScriptModule* cur{};
			ScriptModule* anchor{}; // sentinel (tail)
			ScriptModule* operator*() const { return cur; }
			ScriptModuleIterator& operator++() {
				if (!cur || cur == anchor) { cur = nullptr; return *this; }
				cur = cur->NextScriptModule();
				if (cur == anchor) cur = nullptr;
				return *this;
			}
			bool operator!=(ScriptModuleIterator const& o) const { return cur != o.cur; }
		};

		struct ScriptModuleRange {
			ScriptModule* first{};
			ScriptModule* anchor{};
			std::size_t   maxCnt{};
			ScriptModuleIterator begin() const { return { first,  anchor }; }
			ScriptModuleIterator end() const { return { nullptr, anchor }; }
			std::size_t size() const { return maxCnt; }
		};

		ScriptModuleRange ScriptModules() {
			ScriptModule* first = ScriptModuleHead();
			if (!first) return { nullptr, nullptr, 0 };
			ScriptModule* sentinel = reinterpret_cast<ScriptModule*>(this->Get()->m_ScriptModulesTail); // list terminator
			return { first, sentinel, GetScriptModuleHeap()->Count() }; // guard by heap count
		}

	};

    class NdGameSdk_API ScriptManagerGlobals : public ISdkRegenny<regenny::shared::ndlib::script::ScriptManagerGlobals> {
    public:
		using ScriptCFuncMap = regenny::shared::ndlib::script::ScriptManagerGlobals::ScriptCFuncMap;
        struct NativeFuncEntry {
			StringId64 hash;
            void* Funct;
        };

		bool IsDebugBins();

		ModuleBucketMap* GetBucketModules();
		ModuleBucketMap* GetBucketDebugModules();

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

	static_assert(sizeof(ModuleBucketMap) == 0x1f0, "Size of ModuleBucketMap is not correct.");
}