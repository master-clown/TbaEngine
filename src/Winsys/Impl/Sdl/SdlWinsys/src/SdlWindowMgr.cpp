#include <SdlWinsys/SdlWindowMgr.h>

#include <SdlWinsys/SdlWindow.h>

//======================================================================================================================
using namespace winsys;

//======================================================================================================================
uptr<Window> SdlWindowMgr::createWindow(WindowOptions options)
{
    return std::make_unique<SdlWindow>(std::move(options));
}

