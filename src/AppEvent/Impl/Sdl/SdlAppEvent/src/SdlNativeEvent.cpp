#include <SdlAppEvent/SdlNativeEvent.h>

using namespace app_event;

//======================================================================================================================
SdlNativeEvent::SdlNativeEvent(SDL_Event ev)
    : _sdlEvent(ev)
{
}

//======================================================================================================================
String SdlNativeEvent::str() const
{
    return strFormat("SDL_Event{{.type={:#X}}}", _sdlEvent.type);
}

//======================================================================================================================
const SDL_Event& SdlNativeEvent::getSdlEvent() const
{
    return _sdlEvent;
}
