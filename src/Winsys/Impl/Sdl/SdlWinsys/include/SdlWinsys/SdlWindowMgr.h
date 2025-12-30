#pragma once

#include <Winsys/WindowMgr.h>

//======================================================================================================================
namespace winsys {
    class SdlWindowMgr final : public WindowMgr {
    public:
        uptr<Window> createWindow(WindowOptions) override;
    };
}

