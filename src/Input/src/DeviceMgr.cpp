#include <Input/DeviceMgr.h>

#include <cassert>

using namespace input;

//======================================================================================================================
DeviceMgr::DeviceMgr(framework::Framework& fr)
    : _framework(fr)
{
}

//======================================================================================================================
DeviceMgr::~DeviceMgr() = default;

//======================================================================================================================
void DeviceMgr::update()
{
    getKeyboard().update();
    getMouse().update();
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
Mouse& DeviceMgr::getMouse()
{
    return const_cast<Mouse&>(static_cast<const DeviceMgr&>(*this).getMouse());
}

//----------------------------------------------------------------------------------------------------------------------
const Mouse& DeviceMgr::getMouse() const
{
    assert(_mouse && "Make sure '_setMouse()' is called when creating DeviceMgr");
    return *_mouse;
}

//======================================================================================================================
framework::Framework& DeviceMgr::_getFramework()
{
    return _framework;
}

//======================================================================================================================
void DeviceMgr::_setKeyboard(uptr<Keyboard> keyboard)
{
    _keyboard = std::move(keyboard);
}

//======================================================================================================================
void DeviceMgr::_setMouse(uptr<Mouse> mouse)
{
    _mouse = std::move(mouse);
}
