#pragma once

#include <Input/KeyMods.h>

#include <SDL3/SDL_keyboard.h>

//======================================================================================================================
namespace sdl_input {
    input::KeyMods fromSdlKeyMods(SDL_Keymod);
}
