#include <SdlInput/SdlDeviceMgr.h>

#include <SdlInput/SdlKeyboard.h>

using namespace sdl_input;

//======================================================================================================================
SdlDeviceMgr::SdlDeviceMgr(event_sys::NativeEventListeners& nativeEventListeners)
    : input::DeviceMgr(nativeEventListeners)
{
    _setKeyboard(makeUPtr<SdlKeyboard>());
}
