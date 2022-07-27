//
// Created by reece on 24/07/22.
//

#include "Core/Events/IEventListener.h"
#include "Core/Events/EventManager.h"
#include "Core/common.h"

namespace Venlette::Events {
    IEventListener::IEventListener() noexcept {
        EventManager* manager = EventManager::Get();
        if (!manager) {
            VEN_CORE_ERROR("[EVENT LISTENER] Failed to register: Cannot get EventManager instance");
            return;
        }
        manager->RegisterListener(this);
    }

    IEventListener::IEventListener(Event::Category category) noexcept {
        EventManager* manager = EventManager::Get();
        if (!manager) {
            VEN_CORE_ERROR("[EVENT LISTENER] Failed to register: Cannot get EventManager instance");
            return;
        }
        manager->RegisterListener(this, category);
    }

    IEventListener::~IEventListener() noexcept {
        EventManager* manager = EventManager::Get();
        if (!manager) {
            VEN_CORE_ERROR("[EVENT LISTENER] Failed to unregister: Cannot get EventManager instance");
            return;
        }
        manager->UnregisterListener(this);
    }
} // Events