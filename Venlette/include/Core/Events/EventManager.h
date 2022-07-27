//
// Created by reece on 23/07/22.
//

#pragma once

#include <vector>
#include <queue>

#include "Event.h"
#include "IEventListener.h"


namespace Venlette::Events {

class IEventListener;

class EventManager {
public:
    static bool Init() noexcept;
    static void Shutdown() noexcept;

    static EventManager* Get() noexcept;

    void RegisterListener(IEventListener* listener, Event::Category category=Event::Category::None) noexcept;
    void UnregisterListener(IEventListener* listener) noexcept;

    void PollEvents() noexcept;

    void FireEvent(const Event& event) noexcept;

private:
    static EventManager* s_instance;

    struct Listener {
        IEventListener* listener;
        Event::Category category;
    };

    std::vector<Listener> m_listeners;
    std::queue<Event> m_events;
};


} // Events
