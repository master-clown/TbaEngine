#pragma once

#include <Winsys/WindowMgr.h>

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindowMgr final : public winsys::WindowMgr {
    public:
        explicit SdlWindowMgr(app_event::NativeEventListeners&);
        ~SdlWindowMgr();

        uptr<winsys::Window> createWindow(winsys::WindowOptions) override;
    };
}
