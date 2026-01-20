#pragma once

#include <InputEvent/KeyboardEvent.h>
#include <InputEvent/MouseEvent.h>
#include <WinEvent/WindowEvent.h>

#include <variant>

//======================================================================================================================
namespace app_event {
    //==================================================================================================================
    class AppEvent final {
    public:
        using NoneAppEvent = std::monostate;
        using EventVariant =
            std::variant<
                input_event::KeyboardEvent,
                input_event::MouseEvent,
                win_event::WindowEvent,
                NoneAppEvent>;

        //--------------------------------------------------------------------------------------------------------------
        template <class Event>
        constexpr AppEvent(Event&& ev)
            : _eventVariant(std::move(ev))
        {
        }

        //--------------------------------------------------------------------------------------------------------------
        template <class Event>
        bool is() const;

        template <class Event>
        Event* getIf();

        template <class Event>
        const Event* getIf() const;

        //--------------------------------------------------------------------------------------------------------------
        EventVariant& getVariant();
        const EventVariant& getVariant() const;

    private:
        EventVariant _eventVariant;
    };

    //==================================================================================================================
    constexpr AppEvent noneAppEvent = AppEvent{AppEvent::NoneAppEvent{}};
}
