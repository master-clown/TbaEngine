#pragma once

#include <AppEvent/AppEvent.h>

//======================================================================================================================
namespace app_event {
    class AppEventMgr {
    public:
        virtual ~AppEventMgr();

        virtual AppEvent getNextEvent() = 0;
    };
}
