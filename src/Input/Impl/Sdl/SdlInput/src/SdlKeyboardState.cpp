#include <SdlInput/SdlKeyboardState.h>

using namespace input;
using namespace sdl_input;

//======================================================================================================================
auto SdlKeyboardState::getKeyState(const KeyCode keyCode) const -> KeyState
{
    return KeyState::Released;
}

//======================================================================================================================
KeyMods SdlKeyboardState::getModsState() const
{
    return KeyMods::None;
}
