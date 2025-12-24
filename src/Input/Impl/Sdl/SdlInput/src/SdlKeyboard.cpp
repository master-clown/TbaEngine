#include <SdlInput/SdlKeyboard.h>

#include <SdlInput/SdlKeyboardState.h>

#include <cassert>

using namespace sdl_input;

//======================================================================================================================
SdlKeyboard::SdlKeyboard()
    : input::Keyboard({.type = input::DeviceType::Keyboard, .publicName = "SDL default keyboard"})
    , _keyboardState(makeUPtr<SdlKeyboardState>())
{
}

//======================================================================================================================
SdlKeyboard::~SdlKeyboard() = default;

//======================================================================================================================
void SdlKeyboard::update()
{
}

//======================================================================================================================
const input::KeyboardState& SdlKeyboard::getKeyboardState() const
{
    assert(_keyboardState);
    return *_keyboardState;
}
