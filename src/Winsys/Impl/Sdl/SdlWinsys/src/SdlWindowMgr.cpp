#include <SdlWinsys/SdlWindowMgr.h>

#include <SdlWinsys/SdlWindow.h>

//======================================================================================================================
using namespace sdl_winsys;
using namespace winsys;

//======================================================================================================================
SdlWindowMgr::SdlWindowMgr(event_sys::NativeEventListeners& nativeEventListeners)
    : WindowMgr(nativeEventListeners)
{
}

//======================================================================================================================
SdlWindowMgr::~SdlWindowMgr() = default;

//======================================================================================================================
uptr<Window> SdlWindowMgr::createWindow(WindowOptions options)
{
    return std::make_unique<SdlWindow>(getNativeEventListeners(), std::move(options));
}
