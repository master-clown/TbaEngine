#include <AppEvent/AppEvent.hpp>

//======================================================================================================================
using namespace app_event;

//======================================================================================================================
auto AppEvent::getVariant() -> EventVariant&
{
    return const_cast<EventVariant&>(static_cast<const AppEvent&>(*this).getVariant());
}

//======================================================================================================================
auto AppEvent::getVariant() const -> const EventVariant&
{
    return _eventVariant;
}
