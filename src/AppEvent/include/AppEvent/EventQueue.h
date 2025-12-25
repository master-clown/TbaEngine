#pragma once

#include <AppEvent/AppEvent.h>

#include <Common/Stl/Queue.h>

//======================================================================================================================
namespace app_event {
    class EventQueue final {
    public:
        void push(AppEvent);

    private:
        friend class AppEventMgr;

        AppEvent _pop();
        bool _isEmpty() const;

    private:
        Queue<AppEvent> _queue;
    };
}
