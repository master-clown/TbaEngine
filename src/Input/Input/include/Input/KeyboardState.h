#pragma once

#include <Keyboard/KeyMods.h>
#include <Keyboard/KeyScancode.h>

//======================================================================================================================
namespace input {
    class KeyboardState {
    public:
        virtual ~KeyboardState();

        //--------------------------------------------------------------------------------------------------------------
        enum class KeyState {
            Released,
            Pressed,
        };

        virtual KeyState getKeyState(keyboard::KeyScancode) const = 0;

        //--------------------------------------------------------------------------------------------------------------
        virtual keyboard::KeyMods getModsState() const = 0;
    };
}
