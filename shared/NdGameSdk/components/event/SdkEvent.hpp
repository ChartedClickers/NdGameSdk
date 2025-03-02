#pragma once

#include <Windows.h>
#include <unordered_map>
#include <shared_mutex>
#include <spdlog/spdlog.h>

#include <boost/signals2.hpp>
#include <boost/signals2/slot.hpp>
#include <boost/signals2/signal_type.hpp>
#include <boost/bind/bind.hpp>
#include <boost/functional/hash.hpp>

#include "SdkAction.hpp"
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"


using namespace std;
using namespace boost::signals2;
using namespace Utility::memory;

namespace NdGameSdk {

    template <typename... Args>
    class SdkEvent;
    class ISdkModule;

    template <typename... Args>
    class SdkEvent {
    public:
        using action = void(Args...);
        using delegate = signal<action>;
        using SdkAction = SdkAction<action>;

        template <typename ClassType>
        using ActionInstance = void (ClassType::*)(Args...);

        SdkEvent(bool oneTimeInvoke = false) : m_OneTimeInvoke{ oneTimeInvoke } {}
        ~SdkEvent() { Dispose(); }

        bool CheckIfSubscribed(const SdkAction& action) {
            std::shared_lock lock(m_connections_mtx);
            return m_connections.find(action) != m_connections.end();
        }

        optional<SdkAction> Subscribe(const action& handler, bool oneTimeInvoke = false, connect_position position = at_front) {
            SdkAction sdkAction(handler);
            if (m_disposed || CheckIfSubscribed(sdkAction))
                return {};

            std::unique_lock lock(m_connections_mtx);
            auto conn = Connect(sdkAction, oneTimeInvoke, position);
            m_connections.insert({ sdkAction, conn });
            return sdkAction;
        }

        template <typename ClassType>
        optional<SdkAction> Subscribe(ClassType* instance, ActionInstance<ClassType> memberFunc, bool oneTimeInvoke = false, connect_position position = at_front) {
            SdkAction sdkAction(instance, memberFunc);
            if (m_disposed || CheckIfSubscribed(sdkAction))
                return {};

            std::unique_lock lock(m_connections_mtx);
            auto conn = Connect(sdkAction, oneTimeInvoke, position);
            m_connections.insert({ sdkAction, conn });
            return sdkAction;
        }

        void Unsubscribe(const SdkAction& action) {
            if (m_disposed)
                return;

            std::unique_lock lock(m_connections_mtx);
            auto it = m_connections.find(action);
            if (it != m_connections.end()) {
                if (it->second.connected()) {
                    it->second.disconnect();
                }
                m_connections.erase(it);
            }
        }

        void Unsubscribe(optional<SdkAction>& action) {
            if (action.has_value()) {
                Unsubscribe(action.value());
            }
        }

        optional<SdkAction> operator+=(const action& handler) {
            return Subscribe(handler);
        }

        void operator-=(const action& handler) {
            Unsubscribe(handler);
        }

    private:
        friend class ISdkComponent;
        friend class ISdkModule;

        connection Connect(const SdkAction& sdkAction, bool oneTimeInvoke = false, connect_position position = at_front) {
            if (oneTimeInvoke) {
                SdkEvent<Args...>* thisEvent = this;
                return m_signal.connect_extended([sdkAction, thisEvent](const connection& conn, Args... args) {
                    conn.disconnect();
                    thisEvent->Unsubscribe(sdkAction);
                    sdkAction._function(args...);
                    }, position);
            }
            return m_signal.connect(sdkAction._function, position);
        }

        void UnsubscribeAll() {
            std::unique_lock lock(m_connections_mtx);
            m_signal.disconnect_all_slots();
            m_connections.clear();
        }

        void Dispose() {
            UnsubscribeAll();
            m_disposed = true;
        }

        void Invoke(Args... args) {
            if (m_disposed) return;
            m_signal(args...);
            if (m_OneTimeInvoke) Dispose();
        }

        bool m_OneTimeInvoke{};
        bool m_disposed{};
        delegate m_signal{};
        mutable shared_mutex m_connections_mtx{};
        unordered_map<SdkAction, connection, SdkActionHash, SdkActionHashEqual> m_connections{};
    };

}