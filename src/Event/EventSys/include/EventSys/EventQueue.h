#pragma once

#include <AppEvent/AppEvent.h>
#include <Common/Stl/Queue.h>

//======================================================================================================================
namespace event_sys {
    class EventQueue final {
    public:
        void push(app_event::AppEvent);

    private:
        friend class EventMgr;

        app_event::AppEvent _pop();
        bool _isEmpty() const;

    private:
        Queue<app_event::AppEvent> _queue;
    };
}
