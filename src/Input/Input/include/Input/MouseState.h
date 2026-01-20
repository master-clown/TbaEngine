#pragma once

#include <Mouse/CursorPosition.h>
#include <Mouse/MouseButton.h>

//======================================================================================================================
namespace input {
    class MouseState {
    public:
        virtual ~MouseState();

        //--------------------------------------------------------------------------------------------------------------
        enum class ButtonState {
            Released,
            Pressed,
        };

        virtual ButtonState getButtonState(mouse::MouseButton) const = 0;

        //--------------------------------------------------------------------------------------------------------------
        virtual const mouse::CursorPosition& getCurrentCursorPosition() const = 0;
    };
}
