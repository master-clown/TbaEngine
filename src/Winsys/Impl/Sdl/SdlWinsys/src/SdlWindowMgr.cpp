#include <SdlWinsys/SdlWindowMgr.h>

#include <SdlWinsys/SdlWindow.h>

//======================================================================================================================
using namespace winsys;

//======================================================================================================================
SdlWindowMgr::SdlWindowMgr(app_event::NativeEventListeners& nativeEventListeners)
    : WindowMgr(nativeEventListeners)
{
}

//======================================================================================================================
SdlWindowMgr::~SdlWindowMgr() = default;

//======================================================================================================================
uptr<Window> SdlWindowMgr::createWindow(WindowOptions options)
{
    return std::make_unique<SdlWindow>(std::move(options));
}
