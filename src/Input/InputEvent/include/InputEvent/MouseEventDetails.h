#pragma once

#include <InputEvent/MouseEventKind.h>

#include <Common/String.h>
#include <Keyboard/KeyMods.h>
#include <Mouse/CursorPosition.h>
#include <Mouse/MouseButton.h>

//======================================================================================================================
namespace input_event {
    //==================================================================================================================
    template <MouseEventKind, typename = void>
    struct MouseEventDetails;

    //==================================================================================================================
    template <MouseEventKind eventKind>
    struct MouseEventDetails<eventKind,
                             std::enable_if_t<eventKind == MouseEventKind::ButtonDown ||
                                              eventKind == MouseEventKind::ButtonUp>> /**/ final {
        mouse::MouseButton button;
        keyboard::KeyMods keyboardMods;
    };

    //------------------------------------------------------------------------------------------------------------------
    String str(const MouseEventDetails<MouseEventKind::ButtonDown>&);
    String str(const MouseEventDetails<MouseEventKind::ButtonUp>&);

    //==================================================================================================================
    template <>
    struct MouseEventDetails<MouseEventKind::MouseMoved> final {
        using PositionDelta = mouse::CursorPosition;

        mouse::CursorPosition cursorPos;
        PositionDelta cursorPosDelta;
        mouse::MouseButton pressedButton;
    };

    //------------------------------------------------------------------------------------------------------------------
    String str(const MouseEventDetails<MouseEventKind::MouseMoved>&);

    //==================================================================================================================
    template <>
    struct MouseEventDetails<MouseEventKind::WheelMoved> final {
        using WheelOffset = float;

        WheelOffset x; // positive to the right
        WheelOffset y; // positive away from user
    };

    //------------------------------------------------------------------------------------------------------------------
    String str(const MouseEventDetails<MouseEventKind::WheelMoved>&);
}
