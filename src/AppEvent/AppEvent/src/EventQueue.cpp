#include <AppEvent/EventQueue.h>

#include <cassert>

using namespace app_event;

//======================================================================================================================
void EventQueue::push(AppEvent ev)
{
    _queue.push(std::move(ev));
}

//======================================================================================================================
AppEvent EventQueue::_pop()
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
