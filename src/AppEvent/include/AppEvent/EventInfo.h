#pragma once

#include <any>
#include <concepts>

//======================================================================================================================
namespace app_event {
    //==================================================================================================================
    template <class EventKind, template <auto> class EventDetail>
    concept EventDetailConcept = requires() {
        std::is_default_constructible_v<EventDetail<EventKind{}>>;
    };

    //==================================================================================================================
    template <class EventKind, template <auto> class EventDetail>
        requires EventDetailConcept<EventKind, EventDetail>
    class EventInfo final {
    public:
        explicit EventInfo(EventKind);

        template <EventKind kind>
        explicit EventInfo(EventDetail<kind>);

        EventKind getKind() const;

        template <auto eventKind>
        const EventDetail<eventKind>& getDetail() const;

    private:
        EventKind _kind;
        std::any _detail;
    };
}

