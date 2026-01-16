#include <Input/DeviceMgr.h>

#include <Input/Keyboard.h>

#include <cassert>

using namespace input;

//======================================================================================================================
DeviceMgr::DeviceMgr(event_sys::NativeEventListeners& nativeEventListeners)
    : _nativeEventListeners(nativeEventListeners)
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
event_sys::NativeEventListeners& DeviceMgr::getNativeEventListeners()
{
    return _nativeEventListeners;
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
