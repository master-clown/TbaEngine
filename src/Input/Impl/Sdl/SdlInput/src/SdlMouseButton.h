#pragma once

#include <Mouse/MouseButton.h>

#include <Common/Integers.h>

#include <SDL3/SDL_mouse.h>

//======================================================================================================================
namespace sdl_input {
    using SdlMouseButton = uint8;
    mouse::MouseButton fromSdlMouseButton(SdlMouseButton) noexcept;
    SdlMouseButton toSdlMouseButton(mouse::MouseButton) noexcept;

    // SDL_MouseButtonFlags is truncated to a single button for now
    mouse::MouseButton fromSdlMouseButtonFlags(SDL_MouseButtonFlags) noexcept;
    SDL_MouseButtonFlags toSdlMouseButtonFlags(mouse::MouseButton) noexcept;
}
