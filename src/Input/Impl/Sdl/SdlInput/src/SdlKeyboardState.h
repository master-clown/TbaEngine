#pragma once

#include <Input/KeyboardState.h>

#include <span>

//======================================================================================================================
namespace sdl_input {
    class SdlKeyboardState final : public input::KeyboardState {
    public:
        SdlKeyboardState();

        KeyState getKeyState(keyboard::KeyScancode) const override;
        keyboard::KeyMods getModsState() const override;

    private:
        std::span<const bool> _sdlKeyStates;
    };
}
