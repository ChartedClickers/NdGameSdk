#include <Windows.h>

#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>

#include "NdGameSdk/sdk.hpp"

using namespace std;
using namespace boost::signals2;

namespace NdGameSdk {

    struct NdGameSdk_API ISdkAction {
        uintptr_t _functionAddress{};
        void* _instance{};

        bool operator==(const ISdkAction& other) const {
            return _functionAddress == other._functionAddress
                && _instance == other._instance;
        }
    };

    template <typename action>
    struct NdGameSdk_API SdkAction : public ISdkAction {

        SdkAction(const action& handler) {
            _function = boost::function<action>(handler);
            _functionAddress = reinterpret_cast<uintptr_t>(handler);
        }

        template <typename ClassType, typename...Args>
        SdkAction(ClassType* instance, void (ClassType::* memberFunc)(Args...)) {

            uintptr_t funcAddress{};
            std::memcpy(&funcAddress, &memberFunc, sizeof(funcAddress));

            if constexpr (sizeof...(Args) > 0) {
                constexpr _Ph<sizeof...(Args)> _argscount{};
                _function = boost::bind(memberFunc, instance, _argscount);
            }
            else {
                _function = boost::bind(memberFunc, instance);
            }

            _functionAddress = funcAddress;
            _instance = instance;
        }

        boost::function<action> _function{};
    };

    struct SdkActionHash {
        size_t operator()(const ISdkAction& SdkAction) const {
            std::size_t seed = 0;
            boost::hash_combine(seed, (size_t)SdkAction._functionAddress);

            if (SdkAction._instance) {
                boost::hash_combine(seed, (size_t)SdkAction._instance);
            }

            return seed;
        }
    };

    struct SdkActionHashEqual {
        bool operator()(const ISdkAction& lhs,
            const ISdkAction& rhs) const {
            return lhs == rhs;
        }
    };

}