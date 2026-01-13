#include <SdlEventSys/SdlNativeEvent.h>

using namespace sdl_event_sys;

//======================================================================================================================
SdlNativeEvent::SdlNativeEvent(SDL_Event ev)
    : _sdlEvent(ev)
{
}

//======================================================================================================================
String SdlNativeEvent::str() const
{
    return strFormat("SdlNativeEvent{{.type={:#X}}}", _sdlEvent.type);
}

//======================================================================================================================
const SDL_Event& SdlNativeEvent::getSdlEvent() const
{
    return _sdlEvent;
}
