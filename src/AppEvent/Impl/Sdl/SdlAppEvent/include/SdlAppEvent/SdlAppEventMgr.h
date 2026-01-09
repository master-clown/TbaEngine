#pragma once

#include <AppEvent/AppEventMgr.h>

//======================================================================================================================
namespace sdl_app_event {
    class SdlAppEventMgr final : public app_event::AppEventMgr {
    private:
        Vector<uptr<app_event::NativeEvent>> _fetchNativeEvents() override;
    };
}
