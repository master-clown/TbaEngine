#pragma once

#include <InputEvent/KeyboardEventDetails.h>

//======================================================================================================================
namespace input_event {
    //==================================================================================================================
    template <KeyboardEventKind kind>
    String KeyboardEventDetails<kind>::str() const
    {
        return strFormat("KeyboardEventDetails{{kind={},key={},scan={},mods={}}}",
                         input_event::str(kind),
                         keyboard::str(keyCode),
                         keyboard::str(keyScancode),
                         keyboard::str(keyMods));
    }
}
