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


using namespace std;

namespace NdGameSdk::ndlib::script {

	struct ScriptCFuncInfo {

		enum class TypeOf : uint64_t { None, Bool, Int, Float, StringId, String };

		struct Arguments {
			TypeOf Type;
			string Name;
			string Description;

            uint64_t Data[20]{};
		};

		string Name;
        StringId64 Hash;
        vector<Arguments> Args;
		string Description;
	};



    class ScriptValue : public ISdkRegenny<regenny::shared::ndlib::script::ScriptValue>
    {
    public:
        ScriptValue() = default;
        ScriptValue(std::initializer_list<uint64_t> init) : ScriptValue() {
            if (auto self = this->Get()) {
                size_t n = (std::min)(init.size(), std::size(self->val));
                auto it = init.begin();
                for (size_t i = 0; i < n; ++i, ++it) {
                    self->val[i] = *it;
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
    };


    class ScriptCFunc : public ISdkRegenny<regenny::shared::ndlib::script::ScriptCFunc>
    {
    public:
        void CallScriptCFunc(ScriptValue args, int numArgs, ScriptValue* return_);
        void* GetFunc() const;
    };


    TYPEDEF_EXTERN_FUNCTION_PTR(ScriptCFunc*, ScriptManager_LookupCFunc, StringId64 Lookup, void* return_);

#pragma region JsonSerialize
    inline void to_json(nlohmann::json& j, const ScriptCFuncInfo::TypeOf& t) {
        j = static_cast<uint64_t>(t);
    }

    inline void from_json(const nlohmann::json& j, ScriptCFuncInfo::TypeOf& t) {
        t = static_cast<ScriptCFuncInfo::TypeOf>(j.get<uint64_t>());
    }

    inline void to_json(nlohmann::json& j, const ScriptCFuncInfo::Arguments& a) {
        j = { { "Type",        a.Type },
              { "Name",        a.Name },
              { "Description", a.Description } };
    }

    inline void from_json(const nlohmann::json& j, ScriptCFuncInfo::Arguments& a) {
        j.at("Type").get_to(a.Type);
        j.at("Name").get_to(a.Name);
        j.at("Description").get_to(a.Description);
    }

    inline void to_json(nlohmann::json& j, const ScriptCFuncInfo& s) {
        auto Hash = std::format("0x{:016X}", s.Hash);
        j = { { "Name",  s.Name },
              { "Hash",  Hash },
              { "Description", s.Description },
              { "Args",        s.Args } };
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
}