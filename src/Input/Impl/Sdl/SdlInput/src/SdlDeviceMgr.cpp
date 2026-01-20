#include <SdlInput/SdlDeviceMgr.h>

#include <SdlInput/SdlKeyboard.h>
#include <SdlInput/SdlMouse.h>

using namespace sdl_input;

//======================================================================================================================
SdlDeviceMgr::SdlDeviceMgr(event_sys::NativeEventListeners& nativeEventListeners)
    : input::DeviceMgr(nativeEventListeners)
{
    _setKeyboard(makeUPtr<SdlKeyboard>(getNativeEventListeners()));
    _setMouse(makeUPtr<SdlMouse>(getNativeEventListeners(), *this));
}
