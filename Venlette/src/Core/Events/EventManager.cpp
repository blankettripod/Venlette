//
// Created by reece on 31/07/22.
//

#include "Core/Events/EventManager.h"
#include "Core/internal.h"

namespace Venlette::Events {

    EventManager* EventManager::s_instance = nullptr;

    VEN_RESULT EventManager::Init() noexcept {
        VEN_CORE_INFO("[EVENTS] Initialising");

        if (s_instance) {
            VEN_CORE_ERROR("[EVENTS] Failed to initialise: already initialised");
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



    VEN_RESULT EventManager::AddListener(IEventListener *listener, Event::Category category) noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Failed to add listener: Manager not active");
            return VEN_FAILURE;
        }

        for (auto& l : s_instance->m_listeners) {
            if (l.listener == listener) {
                VEN_CORE_ERROR("[EVENTS] Listener already registered");
                return VEN_FAILURE;
            }
        }

        Listener l{};
        l.listener = listener;
        l.category = category;

        s_instance->m_listeners.push_back(l);

        VEN_CORE_INFO("[EVENTS] Listener registered");
        return VEN_SUCCESS;
    }

    VEN_RESULT EventManager::RemoveListener(const IEventListener *listener) noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Failed to add listener: Manager not active");
            return VEN_FAILURE;
        }

        auto iter = std::find_if(s_instance->m_listeners.begin(), s_instance->m_listeners.end(),
                                         [listener](const Listener& l) {
                                             return l.listener == listener;
                                         });

        if (iter == s_instance->m_listeners.end()) {
            VEN_CORE_ERROR("[EVENTS] Failed to unregister listener: listener not registered");
            return VEN_FAILURE;
        }

        s_instance->m_listeners.erase(iter);
        VEN_CORE_INFO("[EVENTS] Unregistered listener");
        return VEN_SUCCESS;
    }

    VEN_RESULT EventManager::AddEvent(const Event &event) noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Failed to add listener: Manager not active");
            return VEN_FAILURE;
        }


        s_instance->m_events.push(event);
        return VEN_SUCCESS;
    }

    VEN_RESULT EventManager::PollEvents() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[EVENTS] Failed to add listener: Manager not active");
            return VEN_FAILURE;
        }

        while (!s_instance->m_events.empty()) {
            Event event = s_instance->m_events.front();
            s_instance->m_events.pop();

            for (auto& l : s_instance->m_listeners) {
                if (l.category == Event::Category::None || event.category == l.category) {
                    if (l.listener->OnEvent(event)) break;
                }
            }
        }

        return VEN_SUCCESS;
    }
} // Events