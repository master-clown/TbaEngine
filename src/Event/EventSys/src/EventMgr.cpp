#include <EventSys/EventMgr.h>

#include <EventSys/LogCategory.h>
#include <EventSys/NativeEvent.h>
#include <EventSys/NativeEventListener.h>
#include <EventSys/NativeEventProvider.h>

#include <Logger/CategorizedLogging.h>

#include <cassert>

//======================================================================================================================
using namespace event_sys;

//======================================================================================================================
EventMgr::EventMgr(uptr<NativeEventProvider> nativeEventProvider)
    : _nativeEventProvider(std::move(nativeEventProvider))
{
    assert(_nativeEventProvider);
}

//======================================================================================================================
EventMgr::~EventMgr() = default;

//======================================================================================================================
void EventMgr::pollEvents()
{
    const auto nativeEvents = _nativeEventProvider->fetchNewNativeEvents();

    for (const auto& nativeEventPtr : nativeEvents) {
        assert(nativeEventPtr);

        const auto& nativeEvent = *nativeEventPtr;
        bool isNativeEventProcessed = false;
        getNativeEventListeners().forEach([this, &nativeEvent, &isNativeEventProcessed](NativeEventListener& listener) {
            auto appEvent = listener.transformToAppEvent(nativeEvent);
            if (!appEvent.has_value())
                return NativeEventListeners::ListenerTraversalAction::Continue;

            getEventQueue().push(std::move(*appEvent));
            isNativeEventProcessed = true;

            return NativeEventListeners::ListenerTraversalAction::Break;
        });

        if (!isNativeEventProcessed)
            LOG_CATEGORIZED(LogCategory::EventConversionFromNative,
                            logger::LogMessageLevel::Trace,
                            "Skipping NativeEvent={}",
                            nativeEvent.str());
    }
}

//======================================================================================================================
app_event::AppEvent EventMgr::getNextEvent()
{
    if (_eventQueue._isEmpty())
        return app_event::noneAppEvent;

    return _eventQueue._pop();
}

//======================================================================================================================
EventQueue& EventMgr::getEventQueue() const
{
    return _eventQueue;
}

//======================================================================================================================
NativeEventListeners& EventMgr::getNativeEventListeners()
{
    return const_cast<NativeEventListeners&>(static_cast<const EventMgr&>(*this).getNativeEventListeners());
}

//======================================================================================================================
const NativeEventListeners& EventMgr::getNativeEventListeners() const
{
    return _nativeEventListeners;
}
