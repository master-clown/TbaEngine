#include <InputEvent/KeyboardEvent.h>

#include <InputEvent/KeyboardEventDetails.hpp>

#include <EventInfo/EventInfo.hpp>

#include <utility>

//======================================================================================================================
using namespace input_event;

//======================================================================================================================
String input_event::str(const KeyboardEvent& ev)
{
    if (ev.getKind() == KeyboardEventKind::KeyUp)
        return ev.getDetail<KeyboardEventKind::KeyUp>().str();

    if (ev.getKind() == KeyboardEventKind::KeyDown)
        return ev.getDetail<KeyboardEventKind::KeyDown>().str();

    if (ev.getKind() == KeyboardEventKind::KeyRepeat)
        return ev.getDetail<KeyboardEventKind::KeyRepeat>().str();

    std::unreachable();
}
