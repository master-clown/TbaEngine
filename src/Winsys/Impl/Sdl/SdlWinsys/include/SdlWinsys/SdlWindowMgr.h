#pragma once

#include <Winsys/WindowMgr.h>

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindowMgr final : public winsys::WindowMgr {
    public:
        explicit SdlWindowMgr(event_sys::NativeEventListeners&);
        ~SdlWindowMgr();

        uptr<winsys::Window> createWindow(CreateWindowOptions) override;
    };
}
