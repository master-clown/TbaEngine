#pragma once

#include <AppEvent/AppEventMgr.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace app_event {
    class SdlAppEventMgr final : public AppEventMgr {
    public:
        SdlAppEventMgr();
        ~SdlAppEventMgr();

        void update() override;

    private:
        struct Pimpl;
        uptr<Pimpl> _pimpl;
    };
}
