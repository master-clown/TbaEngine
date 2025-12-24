#pragma once

#include <Input/KeyboardState.h>

//======================================================================================================================
namespace sdl_input {
    class SdlKeyboardState final : public input::KeyboardState {
    public:
        KeyState getKeyState(input::KeyCode) const override;
        input::KeyMods getModsState() const override;
    };
}
