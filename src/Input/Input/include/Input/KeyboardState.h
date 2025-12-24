#pragma once

#include <Input/KeyMods.h>
#include <Input/KeyScancode.h>

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

        virtual KeyState getKeyState(KeyScancode) const = 0;

        //--------------------------------------------------------------------------------------------------------------
        virtual KeyMods getModsState() const = 0;
    };
}
