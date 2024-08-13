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

        SdkEvent(bool OneTimeInvoke = false) : m_OneTimeInvoke { OneTimeInvoke } {}
        ~SdkEvent() { Dispose(); };
   

        bool CheckIfSubscribed(const SdkAction& action) {
            std::shared_lock lock{ m_connections_mtx };
            return m_connections.find(action) != m_connections.end();
        }

        optional<SdkAction> Subscribe(const action& handler, bool OneTimeInvoke = false, connect_position position = at_front) {
            
            SdkAction SdkAction(handler);
            if (m_disposed || CheckIfSubscribed(SdkAction)) return {};

            shared_lock lock{ m_connections_mtx };

            auto connect = Connect(SdkAction, OneTimeInvoke, position);
            m_connections.insert({ SdkAction, connect });            
            return SdkAction;
        }

         template <typename ClassType>
         optional<SdkAction> Subscribe(ClassType* instance, ActionInstance<ClassType> memberFunc,
             bool OneTimeInvoke = false, connect_position position = at_front) {

             SdkAction SdkAction(instance, memberFunc);
             if (m_disposed || CheckIfSubscribed(SdkAction)) return {};

             shared_lock lock{ m_connections_mtx };

             auto connect = Connect(SdkAction, OneTimeInvoke, position);
             m_connections.insert({ SdkAction, connect });
             return SdkAction;
         }

         void Unsubscribe(const SdkAction& action) {
             if (m_disposed) { return; }

             shared_lock lock{ m_connections_mtx };
             auto it = m_connections.find(action);

             if (it != m_connections.end()) {
                 connection* conn = &it->second;

                 if (conn->connected()) {
                     conn->disconnect();
                 }

                 m_connections.erase(action);
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

		connection Connect(const SdkAction& SdkAction, bool OneTimeInvoke = false, connect_position position = at_front) {

            if (OneTimeInvoke) {
                SdkEvent<Args...>* SdkEvent = this;
                return m_signal.connect_extended([SdkAction, SdkEvent](const connection& conn, Args... args)
                    {
                        conn.disconnect();
                        SdkEvent->Unsubscribe(SdkAction);
                        SdkAction._function(args...);
                    }, position);
            }

            return m_signal.connect(SdkAction._function, position);
		}

        void UnsubscribeAll() {
            shared_lock lock{ m_connections_mtx };
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
        shared_mutex m_connections_mtx{};
        unordered_map<SdkAction, connection, SdkActionHash, SdkActionHashEqual> m_connections{};
    };

}