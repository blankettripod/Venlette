//
// Created by reece on 31/07/22.
//

#pragma once

#include "Core/Events/Event.h"

namespace Venlette::Events {

    class IEventListener {
    public:
        IEventListener() noexcept;
        explicit IEventListener(Event::Category category) noexcept;

        virtual ~IEventListener() noexcept;

    protected:
        friend class EventManager;
        virtual bool OnEvent(const Event& event) noexcept = 0;
    };

} // Events