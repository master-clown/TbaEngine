#pragma once

#include <Input/KeyCode.h>
#include <Input/KeyMods.h>

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

        virtual KeyState getKeyState(KeyCode) const = 0;

        //--------------------------------------------------------------------------------------------------------------
        virtual KeyMods getModsState() const = 0;
    };
}
