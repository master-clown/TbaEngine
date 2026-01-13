#pragma once

#include <InputEvent/KeyboardEventDetails.h>
#include <InputEvent/KeyboardEventKind.h>

#include <EventInfo/EventInfo.h>

//======================================================================================================================
namespace input_event {
    using KeyboardEvent = event_info::EventInfo<KeyboardEventKind, KeyboardEventDetails>;
}
