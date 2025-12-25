#pragma once

#include <AppEvent/AppEvent.h>
#include <AppEvent/EventQueue.h>

//======================================================================================================================
namespace app_event {
    class AppEventMgr {
    public:
        virtual ~AppEventMgr();

        virtual void update() = 0;

        //--------------------------------------------------------------------------------------------------------------
        AppEvent getNextEvent();
        EventQueue& getEventQueue() const;

    private:
        mutable EventQueue _eventQueue; // change of the queue does not imply change of Mgr
    };
}
