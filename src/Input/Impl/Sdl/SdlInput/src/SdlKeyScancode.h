#pragma once

#include <Input/KeyScancode.h>

#include <SDL3/SDL_scancode.h>

//======================================================================================================================
namespace sdl_input {
    SDL_Scancode toSdlKeyScancode(input::KeyScancode);
}
