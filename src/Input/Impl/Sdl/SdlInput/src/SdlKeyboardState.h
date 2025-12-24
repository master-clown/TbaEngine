#pragma once

#include <Input/KeyboardState.h>

//======================================================================================================================
namespace input {
    class SdlKeyboardState final : public KeyboardState {
    public:
        KeyState getKeyState(KeyCode) const override;
        KeyMods getModsState() const override;
    };
}
