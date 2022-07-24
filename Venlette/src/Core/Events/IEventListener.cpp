//
// Created by reece on 24/07/22.
//

#include "Core/Events/IEventListener.h"
#include "Core/Events/EventManager.h"

namespace Venlette::Events {
    IEventListener::IEventListener() noexcept {
        EventManager::Get()->RegisterListener(this);
    }

    IEventListener::IEventListener(Event::Category category) noexcept {
        EventManager::Get()->RegisterListener(this, category);
    }

    IEventListener::~IEventListener() noexcept {
        EventManager::Get()->UnregisterListener(this);
    }
} // Events