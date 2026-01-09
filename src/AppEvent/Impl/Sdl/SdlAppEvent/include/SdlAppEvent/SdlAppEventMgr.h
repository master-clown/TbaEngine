#pragma once

#include <AppEvent/AppEventMgr.h>

//======================================================================================================================
namespace app_event {
    class SdlAppEventMgr final : public AppEventMgr {
    private:
        Vector<uptr<NativeEvent>> _fetchNativeEvents() override;
    };
}
