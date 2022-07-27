//
// Created by reece on 23/07/22.
//

#pragma once

namespace Venlette::Events {

struct Event {
enum class Type {
    None=0,
    WindowClose, WindowMove, WindowResize, WindowGainFocus,
    WindowLoseFocus, WindowMaximise, WindowMinimise, WindowRestore,
    MouseMove, MousePress, MouseRelease, MouseScroll,
    KeyboardPress, KeyboardRelease, KeyboardChar,
    Client
} type;

enum class Category {
    None=0,
    Mouse,
    Window,
    Keyboard,
} category;

signed data[5];
void* pointer;
};

} // Events
