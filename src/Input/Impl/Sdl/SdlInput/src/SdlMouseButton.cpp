#include "SdlMouseButton.h"

#include <Input/LogCategory.h>
#include <Logger/CategorizedLogging.h>

using namespace sdl_input;

//======================================================================================================================
mouse::MouseButton sdl_input::fromSdlMouseButton(const SdlMouseButton sdlBtn) noexcept
{
    using To = mouse::MouseButton;

    if (sdlBtn == SDL_BUTTON_LEFT)
        return To::Left;

    if (sdlBtn == SDL_BUTTON_RIGHT)
        return To::Right;

    if (sdlBtn == SDL_BUTTON_MIDDLE)
        return To::Middle;

    if (sdlBtn == SDL_BUTTON_X1)
        return To::Side1;

    if (sdlBtn == SDL_BUTTON_X2)
        return To::Side2;

    LOG_CATEGORIZED(input::LogCategory::MouseButtonConversion,
                    logger::LogMessageLevel::Brief,
                    "Unknown SDL_MouseButtonFlags passed ({:#X})",
                    sdlBtn);

    return To::None;
}

//======================================================================================================================
SdlMouseButton sdl_input::toSdlMouseButton(const mouse::MouseButton btn) noexcept
{
    using From = mouse::MouseButton;

    switch (btn) {
    case From::Left: return SDL_BUTTON_LEFT;
    case From::Right: return SDL_BUTTON_RIGHT;
    case From::Middle: return SDL_BUTTON_MIDDLE;
    case From::Side1: return SDL_BUTTON_X1;
    case From::Side2: return SDL_BUTTON_X2;
    default: break;
    }

    LOG_CATEGORIZED(input::LogCategory::MouseButtonConversion,
                    logger::LogMessageLevel::Brief,
                    "Unknown MouseButton passed ({})",
                    str(btn));

    return SDL_MouseButtonFlags{0};
}

//======================================================================================================================
mouse::MouseButton sdl_input::fromSdlMouseButtonFlags(const SDL_MouseButtonFlags sdlBtn) noexcept
{
    using To = mouse::MouseButton;

    if (sdlBtn == SDL_BUTTON_LMASK)
        return To::Left;

    if (sdlBtn == SDL_BUTTON_RMASK)
        return To::Right;

    if (sdlBtn == SDL_BUTTON_MMASK)
        return To::Middle;

    if (sdlBtn == SDL_BUTTON_X1MASK)
        return To::Side1;

    if (sdlBtn == SDL_BUTTON_X2MASK)
        return To::Side2;

    LOG_CATEGORIZED(input::LogCategory::MouseButtonConversion,
                    logger::LogMessageLevel::Brief,
                    "Unknown SDL_MouseButtonFlags passed ({:#X})",
                    sdlBtn);

    return To::None;
}

//======================================================================================================================
SDL_MouseButtonFlags sdl_input::toSdlMouseButtonFlags(const mouse::MouseButton btn) noexcept
{
    using From = mouse::MouseButton;

    switch (btn) {
    case From::Left: return SDL_BUTTON_LMASK;
    case From::Right: return SDL_BUTTON_RMASK;
    case From::Middle: return SDL_BUTTON_MMASK;
    case From::Side1: return SDL_BUTTON_X1MASK;
    case From::Side2: return SDL_BUTTON_X2MASK;
    default: break;
    }

    LOG_CATEGORIZED(input::LogCategory::MouseButtonConversion,
                    logger::LogMessageLevel::Brief,
                    "Unknown MouseButton passed ({})",
                    str(btn));

    return SDL_MouseButtonFlags{0};
}
