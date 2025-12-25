#include "SdlKeyMods.h"

using namespace sdl_input;

//======================================================================================================================
input::KeyMods fromSdlKeyMods(const SDL_Keymod keyMods)
{
    using To = input::KeyMods;

    auto result = To::None;
    if (keyMods & SDL_KMOD_LSHIFT)
        result |= To::LShift;
    if (keyMods & SDL_KMOD_RSHIFT)
        result |= To::RShift;
    if (keyMods & SDL_KMOD_LCTRL)
        result |= To::LCtrl;
    if (keyMods & SDL_KMOD_RCTRL)
        result |= To::RCtrl;
    if (keyMods & SDL_KMOD_LALT)
        result |= To::LAlt;
    if (keyMods & SDL_KMOD_RALT)
        result |= To::RAlt;
    if (keyMods & SDL_KMOD_LGUI)
        result |= To::LGui;
    if (keyMods & SDL_KMOD_RGUI)
        result |= To::RGui;

    return result;
}
