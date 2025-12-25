#include "SdlKeyboardState.h"

#include "SdlKeyMods.h"
#include "SdlKeyScancode.h"

#include <Input/LogCategory.h>
#include <Logger/CategorizedLogging.h>

#include <SDL3/SDL_keyboard.h>

using namespace input;
using namespace sdl_input;

#define LOG(level, ...) LOG_CATEGORIZED(input::LogCategory::KeyboardState, \
                                        logger::LogMessageLevel::level,    \
                                        __VA_ARGS__)

//======================================================================================================================
SdlKeyboardState::SdlKeyboardState()
    : _sdlKeyStates([] {
        int statesSize = 0;
        const auto* states = SDL_GetKeyboardState(&statesSize);

        return std::span<const bool>(states, statesSize);
    }())
{
}

//======================================================================================================================
auto SdlKeyboardState::getKeyState(const KeyScancode scancode) const -> KeyState
{
    static constexpr auto defaultState = KeyState::Released;

    const auto sdlKeyScancode = toSdlKeyScancode(scancode);
    if (sdlKeyScancode == SDL_SCANCODE_UNKNOWN) {
        LOG(Verbose,
            "[!] State of unknown KeyScancode is requested ({})",
            static_cast<std::underlying_type_t<input::KeyScancode>>(scancode));
        return defaultState;
    }

    return _sdlKeyStates[sdlKeyScancode] ? KeyState::Pressed : KeyState::Released;
}

//======================================================================================================================
KeyMods SdlKeyboardState::getModsState() const
{
    return fromSdlKeyMods(SDL_GetModState());
}
