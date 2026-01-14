#pragma once

#include <Common/String.h>

//======================================================================================================================
namespace input_event {
    enum class KeyboardEventKind {
        KeyDown,
        KeyUp,
        KeyRepeat,
    };

    //------------------------------------------------------------------------------------------------------------------
    String str(KeyboardEventKind);
}
