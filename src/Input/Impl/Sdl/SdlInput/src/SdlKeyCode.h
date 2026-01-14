#pragma once

#include <Keyboard/KeyCode.h>

#include <SDL3/SDL_keycode.h>

//======================================================================================================================
namespace sdl_input {
    keyboard::KeyCode fromSdlKeyCode(SDL_Keycode);
    SDL_Keycode toSdlKeyCode(keyboard::KeyCode);
}
