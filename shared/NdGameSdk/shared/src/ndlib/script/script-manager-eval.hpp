#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"
#include "NdGameSdk/database/database.hpp"
#include "NdGameSdk/sdkstringid.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/ScriptValue.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/ScriptCFunc.hpp>
#elif defined(T1X) 
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ScriptValue.hpp>
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ScriptCFunc.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#include "module-info.hpp"
#include "script-module.hpp"

using namespace std;
using namespace Utility::memory;

namespace NdGameSdk::ndlib::script {

    class ScriptValue;

	struct ScriptCFuncInfo {

		enum class TypeOf : uint64_t { None, Bool, Int, Float, StringId, CFuncValue, String };

		struct Arguments {
			TypeOf Type;
			string Name;
			string Description;
            uint64_t Data[20]{};
		};

        ScriptValue makeScriptArgs();

		string Name;
        StringId64 Hash;
        vector<Arguments> Args;
		string Description;
	};

    class NdGameSdk_API ScriptValue : public ISdkRegenny<regenny::shared::ndlib::script::ScriptValue>
    {
    public:
        ScriptValue() = default;
        ScriptValue(std::initializer_list<uint64_t> init);

        template<typename... Ts, typename = std::enable_if_t<(sizeof...(Ts) >= 1)>>
            ScriptValue(Ts&&... ts) : ScriptValue() {
            if (auto self = this->Get()) {
                uint64_t tmp[] = { to_u64(std::forward<Ts>(ts))... };
                constexpr size_t M = std::size(tmp);
                const size_t N = (std::min)(M, std::size(self->val));
                for (size_t i = 0; i < N; ++i) {
                    self->val[i] = tmp[i];
                }
            }
        }

        ScriptValue(ScriptValue&& other) noexcept {
            *this = std::move(other);
        }

        ScriptValue& operator=(ScriptValue&& other) noexcept {
            if (this != &other) {
				auto self = this->Get();
				auto otherSelf = other.Get();
				if (self && otherSelf) {
					for (int i = 0; i < sizeof(self->val) / sizeof(self->val[0]); ++i) {
						self->val[i] = otherSelf->val[i];
					}
				}
				otherSelf->val[0] = 0;
            }
            return *this;
        }

        ScriptValue(const ScriptValue&) = default;
        ScriptValue& operator=(const ScriptValue&) = default;
        ~ScriptValue() = default;

        explicit ScriptValue(const regenny::shared::ndlib::script::ScriptValue& rawValue) {
            if (auto self = this->Get()) {
                *self = rawValue;
            }
        }

        template <typename T>
        T* as() const {
            return (T*)this;
        }

        template <typename T>
        T val(int index) const {
            return (T)this->Get()->val[index];
        }

    private:
        static uint64_t to_u64(uint64_t v) { return v; }
        static uint64_t to_u64(int v) { return static_cast<uint64_t>(v); }
        static uint64_t to_u64(const char* s) { return SID(s); }
        static uint64_t to_u64(const std::string& s) { return SID(s.c_str()); }
        static uint64_t to_u64(float f) {
            uint64_t bits;
            std::memcpy(&bits, &f, sizeof(f));
            return bits;
        }
    };


    class NdGameSdk_API ScriptCFunc : public ISdkRegenny<regenny::shared::ndlib::script::ScriptCFunc>
    {
    public:
        void CallScriptCFunc(ScriptValue args, int numArgs, ScriptValue* return_);
        void* GetFunc() const;

        InlineHook InlinePatchCfunc(void* target_jmp, const wchar_t* source_name, const wchar_t* hook_name);
		MidHook PatchCfunc(MidHookFn target_jmp, const wchar_t* source_name, const wchar_t* hook_name);
        FunctionHook::Ptr MakeFunctionHook(void* target_jmp, const wchar_t* hook_name);
    };

    TYPEDEF_EXTERN_FUNCTION_PTR(void*, ScriptManager_LookupSymbol, StringId64 Lookup, void* return_);
    TYPEDEF_EXTERN_FUNCTION_PTR(ScriptValue*, ScriptManager_LookupInModule, StringId64 Symbol, StringId64 Module);
    TYPEDEF_EXTERN_FUNCTION_PTR(void, ScriptManager_UnbindValue, StringId64 Symbol);

#if defined(T2R)
    TYPEDEF_EXTERN_FUNCTION_PTR(void, ScriptManager_BindValue, StringId64 Symbol, ScriptValue* value, bool isDebugModule, StringId64 module);
#elif defined(T1X)
    TYPEDEF_EXTERN_FUNCTION_PTR(void, ScriptManager_BindValue, StringId64 Symbol, ScriptValue* value, StringId64 module);
#endif

#pragma region JsonSerialize
    inline void to_json(nlohmann::json& j, const ScriptCFuncInfo::TypeOf& t) {
        j = static_cast<uint64_t>(t);
    }

    inline void from_json(const nlohmann::json& j, ScriptCFuncInfo::TypeOf& t) {
        t = static_cast<ScriptCFuncInfo::TypeOf>(j.get<uint64_t>());
    }

    inline void to_json(nlohmann::json& j, const ScriptCFuncInfo::Arguments& a) {

        int last_used = -1;
        for (int i = 0; i < 20; ++i) {
            if (a.Data[i] != 0)
                last_used = i;
        }

        j = { { "Type", a.Type },
              { "Name", a.Name },
              { "Description", a.Description }
        };

        if (last_used >= 0) {
            std::string hex;
            for (int i = 0; i <= last_used; ++i) {
                hex += fmt::format("{:016x}", a.Data[i]);
            }
            j["Data"] = hex;
        }
    }

    inline void from_json(const nlohmann::json& j, ScriptCFuncInfo::Arguments& a) {  
       j.at("Type").get_to(a.Type);  
       j.at("Name").get_to(a.Name);  
       j.at("Description").get_to(a.Description);  

       std::fill(std::begin(a.Data), std::end(a.Data), 0);  

       if (j.contains("Data")) {  
           std::string hex = j.at("Data").get<std::string>();  
           size_t len = hex.length() / 16;  
           len = (std::min)(len, size_t(20)); // Don't overrun  
           for (size_t i = 0; i < len; ++i) {  
               auto substr = hex.substr(i * 16, 16);  
               a.Data[i] = std::stoull(substr, nullptr, 16);  
           }  
       }  
    }

    inline void to_json(nlohmann::json& j, const ScriptCFuncInfo& s) {
        auto Hash = std::format("0x{:016X}", s.Hash);
        j = { { "Name", s.Name },
              { "Hash", Hash },
              { "Description", s.Description },
              { "Args", s.Args } };
    }

    inline void from_json(const nlohmann::json& j, ScriptCFuncInfo& s) {
        j.at("Name").get_to(s.Name);
        {
            auto hs = j.at("Hash").get<std::string>();
            s.Hash = static_cast<StringId64>(std::stoull(hs, nullptr, 0));
        }
        j.at("Description").get_to(s.Description);
        j.at("Args").get_to(s.Args);
    }
#pragma endregion

	static_assert(sizeof(ScriptValue) == 0x80, "Size of ScriptValue is not correct.");
    static_assert(sizeof(ScriptCFunc) == 0x10, "Size of ScriptCFunc is not correct.");
}