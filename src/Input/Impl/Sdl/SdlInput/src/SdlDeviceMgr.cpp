#include <SdlInput/SdlDeviceMgr.h>

#include <SdlInput/SdlKeyboard.h>

using namespace sdl_input;

//======================================================================================================================
SdlDeviceMgr::SdlDeviceMgr()
{
    _setKeyboard(makeUPtr<SdlKeyboard>());
}
