//
// Created by reece on 31/07/22.
//

#pragma once

namespace Venlette::Events {

    struct Event {
        enum class Type {
            None=0,
            WindowClose, WindowMove, WindowGainFocus, WindowLoseFocus,
            MouseMove, MousePress, MouseRelease, MouseScroll,
            KeyboardPress, KeyboardRelease, KeyboardChar,
        } type;

        enum Category {
            None=0,
            Window,
            Mouse,
            Keyboard,
        } category;

        int data[5];
    };

} // Events