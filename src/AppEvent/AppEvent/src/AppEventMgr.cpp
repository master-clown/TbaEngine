#include <AppEvent/AppEventMgr.h>

#include <AppEvent/LogCategory.h>
#include <AppEvent/NativeEvent.h>
#include <AppEvent/NativeEventListener.h>

#include <Logger/CategorizedLogging.h>

#include <cassert>

//======================================================================================================================
using namespace app_event;

//======================================================================================================================
AppEventMgr::~AppEventMgr() = default;

//======================================================================================================================
void AppEventMgr::pollEvents()
{
    const auto nativeEvents = _fetchNativeEvents();

    for (const auto& nativeEventPtr : nativeEvents) {
        assert(nativeEventPtr);

        const auto& nativeEvent = *nativeEventPtr;
        bool isNativeEventProcessed = false;
        getNativeEventListeners().forEach([this, &nativeEvent, &isNativeEventProcessed](NativeEventListener& listener) {
            auto appEvent = listener.processNativeEvent(nativeEvent);
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
AppEvent AppEventMgr::getNextEvent()
{
    if (_eventQueue._isEmpty())
        return NoneAppEvent{};

    return _eventQueue._pop();
}

//======================================================================================================================
EventQueue& AppEventMgr::getEventQueue() const
{
    return _eventQueue;
}

//======================================================================================================================
NativeEventListeners& AppEventMgr::getNativeEventListeners()
{
    return const_cast<NativeEventListeners&>(static_cast<const AppEventMgr&>(*this).getNativeEventListeners());
}

//======================================================================================================================
const NativeEventListeners& AppEventMgr::getNativeEventListeners() const
{
    return _nativeEventListeners;
}
