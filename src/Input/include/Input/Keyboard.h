#pragma once

#include <Input/Device.h>

//======================================================================================================================
namespace input {
    class KeyboardState;
}

//======================================================================================================================
namespace input {
    class Keyboard : public Device {
    public:
        // TODO: add `+ {abstract} allowTextInputEvents() -> TextInputEventsGuard`

        virtual const KeyboardState& getKeyboardState() const = 0;
    };
}
