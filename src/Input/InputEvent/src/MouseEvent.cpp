#include <InputEvent/MouseEvent.h>

#include <InputEvent/MouseEventDetails.h>

#include <EventInfo/EventInfo.hpp>

#include <utility>

//======================================================================================================================
using namespace input_event;

//======================================================================================================================
String input_event::str(const MouseEvent& ev)
{
    if (ev.getKind() == MouseEventKind::ButtonDown)
        return str(ev.getDetail<MouseEventKind::ButtonDown>());

    if (ev.getKind() == MouseEventKind::ButtonUp)
        return str(ev.getDetail<MouseEventKind::ButtonUp>());

    if (ev.getKind() == MouseEventKind::MouseMoved)
        return str(ev.getDetail<MouseEventKind::MouseMoved>());

    if (ev.getKind() == MouseEventKind::WheelMoved)
        return str(ev.getDetail<MouseEventKind::WheelMoved>());

    std::unreachable();
}
