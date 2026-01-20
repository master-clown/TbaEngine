#pragma once

#include <Common/String.h>

//======================================================================================================================
namespace input_event {
    enum class MouseEventKind {
        ButtonDown,
        ButtonUp,
        MouseMoved,
        WheelMoved,
    };

    //------------------------------------------------------------------------------------------------------------------
    String str(MouseEventKind);
}
