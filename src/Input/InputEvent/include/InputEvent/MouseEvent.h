#pragma once

#include <InputEvent/MouseEventDetails.h>
#include <InputEvent/MouseEventKind.h>

#include <Common/String.h>
#include <EventInfo/EventInfo.h>

//======================================================================================================================
namespace input_event {
    using MouseEvent = event_info::EventInfo<MouseEventKind, MouseEventDetails>;

    //------------------------------------------------------------------------------------------------------------------
    String str(const MouseEvent&);
}
