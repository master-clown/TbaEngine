#include <Input/DeviceMgr.h>

#include <Input/Keyboard.h>

#include <cassert>

using namespace input;

//======================================================================================================================
DeviceMgr::DeviceMgr()
{
}

//======================================================================================================================
DeviceMgr::~DeviceMgr() = default;

//======================================================================================================================
void DeviceMgr::update()
{
    getKeyboard().update();
}

//======================================================================================================================
Keyboard& DeviceMgr::getKeyboard()
{
    return const_cast<Keyboard&>(static_cast<const DeviceMgr&>(*this).getKeyboard());
}

//----------------------------------------------------------------------------------------------------------------------
const Keyboard& DeviceMgr::getKeyboard() const
{
    assert(_keyboard && "Make sure '_setKeyboard()' is called when creating DeviceMgr");
    return *_keyboard;
}

//======================================================================================================================
void DeviceMgr::_setKeyboard(uptr<Keyboard> keyboard)
{
    _keyboard = std::move(keyboard);
}
