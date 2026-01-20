#include <InputEvent/MouseEventKind.h>

#include <utility>

//======================================================================================================================
String input_event::str(const input_event::MouseEventKind kind)
{
    using En = input_event::MouseEventKind;

    switch (kind) {
    case En::ButtonDown: return "KeyboardEventKind::KeyDown";
    case En::ButtonUp: return "KeyboardEventKind::KeyUp";
    case En::MouseMoved: return "KeyboardEventKind::MouseMoved";
    case En::WheelMoved: return "KeyboardEventKind::WheelMoved";
    default: std::unreachable();
    }
}
