#pragma once

#include <EventInfo/EventInfo.h>

#include <cassert>

//======================================================================================================================
namespace event_info {
    //==================================================================================================================
    template <class EventKind, template <auto> class EventDetail>
        requires EventDetailConcept<EventKind, EventDetail>
    EventInfo<EventKind, EventDetail>::EventInfo(const EventKind kind)
        : _kind(kind)
    {
    }

    //------------------------------------------------------------------------------------------------------------------
    template <class EventKind, template <auto> class EventDetail>
        requires EventDetailConcept<EventKind, EventDetail>
    template <EventKind kind>
    EventInfo<EventKind, EventDetail>::EventInfo(EventDetail<kind> detail)
        : _kind(kind)
        , _detail(std::move(detail))
    {
    }

    //==================================================================================================================
    template <class EventKind, template <auto> class EventDetail>
        requires EventDetailConcept<EventKind, EventDetail>
    EventKind EventInfo<EventKind, EventDetail>::getKind() const
    {
        return _kind;
    }

    //==================================================================================================================
    template <class EventKind, template <auto> class EventDetail>
        requires EventDetailConcept<EventKind, EventDetail>
    template <auto eventKind>
    const EventDetail<eventKind>& EventInfo<EventKind, EventDetail>::getDetail() const
    {
        static_assert(std::is_same_v<decltype(eventKind), EventKind>,
                      "It is expected that EventDetail is templated by EventKind");

        if (!_detail.has_value()) {
            static const EventDetail<eventKind> emptyEventDetail{};
            return emptyEventDetail;
        }

        const auto* detail = std::any_cast<EventDetail<eventKind>>(&_detail);
        assert(detail && "This EventInfo contains event detail of another kind.");
        return *detail;
    }
}
