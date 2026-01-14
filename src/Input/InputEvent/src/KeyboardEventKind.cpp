#include <InputEvent/KeyboardEventKind.h>

#include <utility>

//======================================================================================================================
String input_event::str(const input_event::KeyboardEventKind kind)
{
    using En = input_event::KeyboardEventKind;

    switch (kind) {
    case En::KeyDown: return "KeyboardEventKind::KeyDown";
    case En::KeyUp: return "KeyboardEventKind::KeyUp";
    case En::KeyRepeat: return "KeyboardEventKind::KeyRepeat";
    default: std::unreachable();
    }
}
