#pragma once

#include <Keyboard/KeyMods.h>

#include <SDL3/SDL_keyboard.h>

//======================================================================================================================
namespace sdl_input {
    keyboard::KeyMods fromSdlKeyMods(SDL_Keymod);
}
