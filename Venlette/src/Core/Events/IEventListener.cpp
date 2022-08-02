//
// Created by reece on 31/07/22.
//

#include "Core/Events/IEventListener.h"
#include "Core/internal.h"

#include "Core/Events/EventManager.h"

namespace Venlette::Events {
    IEventListener::IEventListener() noexcept {
        EventManager::Get()->AddListener(this);
    }

    IEventListener::IEventListener(Event::Category category) noexcept {
        EventManager::Get()->AddListener(this, category);
    }

    IEventListener::~IEventListener() noexcept {
        EventManager::Get()->RemoveListener(this);
    }
} // Events