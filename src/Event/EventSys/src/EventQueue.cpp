#include <EventSys/EventQueue.h>

#include <cassert>

using namespace event_sys;

//======================================================================================================================
void EventQueue::push(app_event::AppEvent ev)
{
    _queue.push(std::move(ev));
}

//======================================================================================================================
app_event::AppEvent EventQueue::_pop()
{
    assert(!_isEmpty());
    auto ev = std::move(_queue.front());
    _queue.pop();
    return ev;
}

//======================================================================================================================
bool EventQueue::_isEmpty() const
{
    return _queue.empty();
}
