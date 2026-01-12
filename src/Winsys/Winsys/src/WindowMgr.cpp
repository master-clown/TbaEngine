#include <Winsys/WindowMgr.h>

//======================================================================================================================
using winsys::WindowMgr;

//======================================================================================================================
WindowMgr::WindowMgr(event_sys::NativeEventListeners& nativeEventListeners)
    : _nativeEventListeners(nativeEventListeners)
{
}

//======================================================================================================================
WindowMgr::~WindowMgr() = default;

//======================================================================================================================
event_sys::NativeEventListeners& WindowMgr::getNativeEventListeners()
{
    return _nativeEventListeners;
}
