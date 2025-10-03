#include <Winsys/SdlWindowMgr.h>

#include <Winsys/SdlWindow.h>

//======================================================================================================================
using namespace winsys;

//======================================================================================================================
uptr<Window> SdlWindowMgr::createWindow(WindowOptions options)
{
    return std::make_unique<SdlWindow>(std::move(options));
}

