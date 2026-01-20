#pragma once

#include <Mouse/CursorPosition.h>

//======================================================================================================================
namespace sdl_input {
    using SdlWinCoord = float;

    mouse::CursorPosition fromSdlCursorPosition(SdlWinCoord x, SdlWinCoord y) noexcept;
}
