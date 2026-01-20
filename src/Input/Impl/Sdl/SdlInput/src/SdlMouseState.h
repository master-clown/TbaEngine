#pragma once

#include <Input/MouseState.h>

//======================================================================================================================
namespace sdl_input {
    class SdlMouseState final : public input::MouseState {
    public:
        SdlMouseState();

        ButtonState getButtonState(mouse::MouseButton) const override;
        const mouse::CursorPosition& getCurrentCursorPosition() const override;

    private:
        static mouse::CursorPosition _getCurrentCursorPosFromSdl() noexcept;

    private:
        mutable mouse::CursorPosition _currentCursorPos;
    };
}
