#pragma once

#include <Common/Memory.h>
#include <Input/Keyboard.h>

//======================================================================================================================
namespace sdl_input {
    class SdlKeyboard final : public input::Keyboard {
    public:
        SdlKeyboard();
        ~SdlKeyboard();

        void update() override;

        const input::KeyboardState& getKeyboardState() const override;

    private:
        uptr<input::KeyboardState> _keyboardState;
    };
}
