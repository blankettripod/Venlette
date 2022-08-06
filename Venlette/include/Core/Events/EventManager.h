//
// Created by reece on 31/07/22.
//

#pragma once

#include "Core/common.h"
#include "Core/Events/Event.h"
#include "Core/Events/IEventListener.h"

namespace Venlette::Core{class Engine;}

namespace Venlette::Events {

    class EventManager {
    public:
        static VEN_RESULT AddListener(IEventListener *listener, Event::Category category=Event::Category::None) noexcept;
        static VEN_RESULT RemoveListener(const IEventListener *listener) noexcept;

        static VEN_RESULT AddEvent(const Event& event) noexcept;
        static VEN_RESULT PollEvents() noexcept;

    protected:
        friend class Venlette::Core::Engine;

        static VEN_RESULT Init() noexcept;
        static VEN_RESULT Shutdown() noexcept;

    private:
        static EventManager* s_instance;

        struct Listener{
            IEventListener* listener;
            Event::Category category;
        };

        std::vector<Listener> m_listeners;
        std::queue<Event> m_events;
    };


} // Events