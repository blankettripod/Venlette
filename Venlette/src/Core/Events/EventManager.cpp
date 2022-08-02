//
// Created by reece on 31/07/22.
//

#include "Core/Events/EventManager.h"
#include "Core/internal.h"

#include "Core/Thread/ThreadManager.h"

namespace Venlette::Events {

    EventManager* EventManager::s_instance = nullptr;

    VEN_RESULT EventManager::Init() noexcept {
        if (s_instance) {
            VEN_CORE_WARN("[EVENTS] Reinitialising");
        } else {
            VEN_CORE_INFO("[EVENTS] Initialising");
        }

        try {
            s_instance = new EventManager;
        } catch (std::bad_alloc& e) {
            VEN_CORE_ERROR("[EVENTS] Failed to initialise: Failed to allocate memory");
            return VEN_FAILURE;
        } catch (std::exception& e) {
            VEN_CORE_ERROR("[EVENTS] Failed to initialise: {}", e.what());
            return VEN_FAILURE;
        } catch (std::string& e) {
            VEN_CORE_ERROR("[EVENTS] Failed to initialise: {}", e);
            return VEN_FAILURE;
        }

        VEN_CORE_INFO("[EVENTS] Initialised");
        return VEN_SUCCESS;
    }

    VEN_RESULT EventManager::Shutdown() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Failed to shutdown: Manager not active");
            return VEN_FAILURE;
        }

        try {
            delete s_instance;
        } catch (std::exception& e) {
            VEN_CORE_ERROR("[EVENTS] Failed to shutdown: {}", e.what());
        } catch (std::string& e) {
            VEN_CORE_ERROR("[EVENTS] Failed to shutdown: {}", e);
        }

        s_instance = nullptr;
        VEN_CORE_INFO("[EVENTS] Shutdown");
        return VEN_SUCCESS;
    }

    EventManager *EventManager::Get() noexcept {
        if (s_instance) return s_instance;
        VEN_CORE_ERROR("[EVENTS] Cannot get instance: Instance not available");
        return nullptr;
    }

    VEN_RESULT EventManager::AddListener(IEventListener *listener, Event::Category category) noexcept {
        for (auto& l : m_listeners) {
            if (l.listener == listener) {
                VEN_CORE_ERROR("[EVENTS] Listener already registered");
                return VEN_FAILURE;
            }
        }

        Listener l{};
        l.listener = listener;
        l.category = category;

        m_listeners.push_back(l);

        VEN_CORE_INFO("[EVENTS] Listener registered");
        return VEN_SUCCESS;
    }

    VEN_RESULT EventManager::RemoveListener(const IEventListener *listener) noexcept {
        auto iter = std::find_if(m_listeners.begin(), m_listeners.end(),
                                         [listener](const Listener& l) {
                                             return l.listener == listener;
                                         });

        if (iter == m_listeners.end()) {
            VEN_CORE_ERROR("[EVENTS] Failed to unregister listener: listener not registered");
            return VEN_FAILURE;
        }

        m_listeners.erase(iter);
        VEN_CORE_INFO("[EVENTS] Unregistered listener");
        return VEN_SUCCESS;
    }

    VEN_RESULT EventManager::AddEvent(const Event &event) noexcept {
        m_events.push(event);
        return VEN_SUCCESS;
    }

    VEN_RESULT EventManager::PollEvents() noexcept {
        if (FAILED(IS_THREAD_OF_TYPE(Threading::ThreadType::ClientUpdate))) {
            VEN_CORE_ERROR("[EVENTS] EventManager::PollEvents called from unexpected thread: MUST be called from the client update thread");
            return VEN_FAILURE;
        }

        while (!m_events.empty()) {
            Event event = m_events.front();
            m_events.pop();

            for (auto& l : m_listeners) {
                if (l.category == Event::Category::None || event.category == l.category) {
                    if (l.listener->OnEvent(event)) break;
                }
            }
        }

        return VEN_SUCCESS;
    }
} // Events