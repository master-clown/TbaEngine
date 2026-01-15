#pragma once

#include <AppEvent/AppEvent.h>

//======================================================================================================================
namespace app_event {
    //==================================================================================================================
    template <class Event>
    bool AppEvent::is() const
    {
        return std::holds_alternative<Event>(_eventVariant);
    }

    //==================================================================================================================
    template <class Event>
    Event* AppEvent::getIf()
    {
        return std::get_if<Event>(&_eventVariant);
    }

    //------------------------------------------------------------------------------------------------------------------
    template <class Event>
    const Event* AppEvent::getIf() const
    {
        return std::get_if<Event>(&_eventVariant);
    }
}
