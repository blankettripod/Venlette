//
// Created by reece on 23/07/22.
//

#include "Core/Events/EventManager.h"
#include "Util/Logging/Logger.h"

namespace Venlette::Events {

EventManager* EventManager::s_instance = nullptr;

void EventManager::Init() noexcept {
    if (s_instance) {
        VEN_CORE_ERROR("EventManager already initialized!");
        return;
    }
    try {
        s_instance = new EventManager;
    } catch (const std::exception& e) {
        VEN_CORE_ERROR("Failed to initialize EventManager: {}", e.what());
        return;
    }

    VEN_CORE_INFO("EventManager initialized!");
}

    void EventManager::Shutdown() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("Cannot Shutdown EventManager: EventManager not initialized!");
            return;
        }
        delete s_instance;
        s_instance = nullptr;

        VEN_CORE_INFO("EventManager shutdown!");
    }

    EventManager *EventManager::Get() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("Cannot Get EventManager: EventManager not initialized!");
            return nullptr;
        }
        return s_instance;
    }

    void EventManager::RegisterListener(IEventListener *listener, Event::Category category) noexcept {
        if (!listener) {
            VEN_CORE_ERROR("Cannot Register Listener: Listener is null!");
            return;
        }

        // Check if listener is already registered using find
        auto it = std::find_if(m_listeners.begin(), m_listeners.end(), [listener](const Listener& l) {
            return l.listener == listener;
        });
        if (it != m_listeners.end()) {
            VEN_CORE_WARN("Listener already registered!");
            return;
        }

        m_listeners.push_back({listener, category});
    }

    void EventManager::UnregisterListener(IEventListener *listener) noexcept {
        if (!listener) {
            VEN_CORE_ERROR("Cannot Unregister Listener: Listener is null!");
            return;
        }

        // Check if listener is already registered using find
        auto it = std::find_if(m_listeners.begin(), m_listeners.end(), [listener](const Listener& l) {
            return l.listener == listener;
        });
        if (it == m_listeners.end()) {
            VEN_CORE_WARN("Listener not registered!");
            return;
        }

        m_listeners.erase(it);
    }

    void EventManager::AddEvent(const Event &event) noexcept {
        if (event.type == Event::Type::None) {
            VEN_CORE_WARN("Event is null!");
            return;
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