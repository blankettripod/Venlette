//
// Created by reece on 23/07/22.
//

#include "Core/Events/EventManager.h"
#include "Core/common.h"

namespace Venlette::Events {

    EventManager* EventManager::s_instance = nullptr;

    bool EventManager::Init() noexcept {
        if (s_instance) {
            VEN_CORE_WARN("[EVENTS] Already initialized");

            delete s_instance;
            s_instance = nullptr;
        }

        try {
            s_instance = new EventManager;

        } catch (const std::exception& e) {
            VEN_CORE_ERROR("[EVENTS] Failed to initialize: {}", e.what());

            delete s_instance;
            s_instance = nullptr;

            return false;
        }

        VEN_CORE_INFO("[EVENTS] Initialized");
        return true;
    }

    void EventManager::Shutdown() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Cannot shutdown: Not initialized");
            return;
        }

        delete s_instance;
        s_instance = nullptr;

        VEN_CORE_INFO("[EVENTS] Shutdown");
    }

    EventManager *EventManager::Get() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Cannot get instance: Not initialized");
            return nullptr;
        }
        return s_instance;
    }

    void EventManager::RegisterListener(IEventListener *listener, Event::Category category) noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Cannot register listener: Not initialized");
            return;
        }

        if (!listener) {
            VEN_CORE_ERROR("[EVENTS] Cannot register listener: Listener is null");
            return;
        }

        auto it = std::find_if(m_listeners.begin(), m_listeners.end(), [listener](const Listener& l) {
            return l.listener == listener;
        });

        if (it != m_listeners.end()) {

            if (it->category == category) {
                // we are registering with the same category, so this should NOT go ahead
                VEN_CORE_ERROR("[EVENTS] Cannot register listener: Listener is already registered with same category");
                return;
            }

            VEN_CORE_WARN("[EVENTS] Registering listener again with different category");
            m_listeners.erase(it);
        }

        VEN_CORE_INFO("[EVENTS] Registered Listener");
        m_listeners.push_back({listener, category});
    }

    void EventManager::UnregisterListener(IEventListener *listener) noexcept {
        if (!listener) {
            VEN_CORE_ERROR("[EVENTS] Cannot unregister listener: Listener is null");
            return;
        }

        // Check if listener is already registered using find
        auto it = std::find_if(m_listeners.begin(), m_listeners.end(), [listener](const Listener& l) {
            return l.listener == listener;
        });
        if (it == m_listeners.end()) {
            VEN_CORE_ERROR("[EVENTS] Cannot unregister listener: listener not registered");
            return;
        }

        VEN_CORE_INFO("[EVENTS] Unregistered Listener");
        m_listeners.erase(it);
    }

    void EventManager::FireEvent(const Event &event) noexcept {
        if (event.type == Event::Type::None) {
            VEN_CORE_WARN("[EVENTS] Null event received");
        }

        m_events.push(event);
    }

    void EventManager::PollEvents() noexcept {
        while (!m_events.empty()) {
            auto event = m_events.front();
            m_events.pop();

            for (auto& listener : m_listeners) {
                if (listener.category == Event::Category::None || listener.category == event.category) {
                    listener.listener->OnEvent(event);
                }
            }
        }

    }


} // Events