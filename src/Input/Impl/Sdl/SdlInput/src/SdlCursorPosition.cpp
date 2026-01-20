#include "SdlCursorPosition.h"

#include <Common/NumericCast.hpp>

//======================================================================================================================
using namespace sdl_input;

//======================================================================================================================
mouse::CursorPosition sdl_input::fromSdlCursorPosition(const SdlWinCoord sdlX, const SdlWinCoord sdlY) noexcept
{
    return {
        .x = numericCast<mouse::CursorPosition::WindowCoordinate>(sdlX),
        .y = numericCast<mouse::CursorPosition::WindowCoordinate>(sdlY),
    };
}
