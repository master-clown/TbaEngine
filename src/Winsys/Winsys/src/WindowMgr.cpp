#include <Winsys/WindowMgr.h>

//======================================================================================================================
using winsys::WindowMgr;

//======================================================================================================================
WindowMgr::WindowMgr(app_event::NativeEventListeners& nativeEventListeners)
    : _nativeEventListeners(nativeEventListeners)
{
}

//======================================================================================================================
WindowMgr::~WindowMgr() = default;

//======================================================================================================================
app_event::NativeEventListeners& WindowMgr::getNativeEventListeners()
{
    return _nativeEventListeners;
}
