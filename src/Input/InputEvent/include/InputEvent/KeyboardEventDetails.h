#pragma once

#include <InputEvent/KeyboardEventKind.h>

#include <Common/String.h>
#include <Keyboard/KeyCode.h>
#include <Keyboard/KeyMods.h>
#include <Keyboard/KeyScancode.h>

//======================================================================================================================
namespace input_event {
    //==================================================================================================================
    template <KeyboardEventKind>
    struct KeyboardEventDetails final {
        keyboard::KeyCode keyCode;
        keyboard::KeyScancode keyScancode;
        keyboard::KeyMods keyMods;

        String str() const;
    };
}
