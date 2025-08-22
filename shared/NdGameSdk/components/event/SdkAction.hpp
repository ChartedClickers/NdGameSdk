#pragma once
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
                if constexpr (sizeof...(Args) == 1) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1);
                } else if constexpr (sizeof...(Args) == 2) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2);
                } else if constexpr (sizeof...(Args) == 3) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3);
                } else if constexpr (sizeof...(Args) == 4) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3, boost::placeholders::_4);
                } else if constexpr (sizeof...(Args) == 5) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3, boost::placeholders::_4, boost::placeholders::_5);
                } else if constexpr (sizeof...(Args) == 6) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3, boost::placeholders::_4, boost::placeholders::_5, boost::placeholders::_6);
                } else if constexpr (sizeof...(Args) == 7) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3, boost::placeholders::_4, boost::placeholders::_5, boost::placeholders::_6, boost::placeholders::_7);
                } else if constexpr (sizeof...(Args) == 8) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3, boost::placeholders::_4, boost::placeholders::_5, boost::placeholders::_6, boost::placeholders::_7, boost::placeholders::_8);
                } else if constexpr (sizeof...(Args) == 9) {
                    _function = boost::bind(memberFunc, instance, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3, boost::placeholders::_4, boost::placeholders::_5, boost::placeholders::_6, boost::placeholders::_7, boost::placeholders::_8, boost::placeholders::_9);
                }
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