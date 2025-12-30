#pragma once

#include <AppEvent/EventInfo.h>
#include <AppEvent/WindowEventDetails.h>
#include <AppEvent/WindowEventKind.h>

//======================================================================================================================
namespace app_event {
    using WindowEvent = EventInfo<WindowEventKind, WindowEventDetails>;
}
