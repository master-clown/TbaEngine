#pragma once

#include <WinEvent/WindowEventDetails.h>
#include <WinEvent/WindowEventKind.h>

#include <EventInfo/EventInfo.h>

//======================================================================================================================
namespace win_event {
    using WindowEvent = event_info::EventInfo<WindowEventKind, WindowEventDetails>;
}
