#pragma once

#include <Winsys/WindowMgr.h>

//======================================================================================================================
namespace winsys {
    class SdlWindowMgr final : public WindowMgr {
    public:
        explicit SdlWindowMgr(app_event::NativeEventListeners&);
        ~SdlWindowMgr();

        uptr<Window> createWindow(WindowOptions) override;
    };
}
