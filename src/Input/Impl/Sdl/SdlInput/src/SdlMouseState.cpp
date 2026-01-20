#include "SdlMouseState.h"

#include "SdlCursorPosition.h"
#include "SdlMouseButton.h"

#include <SDL3/SDL_mouse.h>

using namespace input;
using namespace mouse;
using namespace sdl_input;

//======================================================================================================================
SdlMouseState::SdlMouseState()
    : _currentCursorPos(SdlMouseState::_getCurrentCursorPosFromSdl())
{
}

//======================================================================================================================
auto SdlMouseState::getButtonState(const mouse::MouseButton btn) const -> ButtonState
{
    const auto sdlRequestedBtn = toSdlMouseButtonFlags(btn);
    const auto sdlBtnFlags = SDL_GetMouseState(nullptr, nullptr);

    return ((sdlBtnFlags & sdlRequestedBtn) != 0) ? ButtonState::Pressed : ButtonState::Released;
}

//======================================================================================================================
const CursorPosition& SdlMouseState::getCurrentCursorPosition() const
{
    return (_currentCursorPos = SdlMouseState::_getCurrentCursorPosFromSdl());
}

//======================================================================================================================
CursorPosition SdlMouseState::_getCurrentCursorPosFromSdl() noexcept
{
    SdlWinCoord sdlPosX;
    SdlWinCoord sdlPosY;

    SDL_GetMouseState(&sdlPosX, &sdlPosY);

    return fromSdlCursorPosition(sdlPosX, sdlPosY);
}
