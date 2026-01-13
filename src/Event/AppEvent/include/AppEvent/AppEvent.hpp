#pragma once

#include <AppEvent/AppEvent.h>

//======================================================================================================================
namespace app_event {
    template <class Event>
    bool AppEvent::is() const
    {
        return std::holds_alternative<Event>(_eventVariant);
    }
}
