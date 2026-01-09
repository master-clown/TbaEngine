#include <AppEvent/NativeEventListeners.h>

#include <atomic>
#include <cassert>

using namespace app_event;

//======================================================================================================================
NativeEventListeners::NativeEventListeners() = default;

//======================================================================================================================
NativeEventListeners::~NativeEventListeners()
{
    assert(_listenersMap.empty() && "It is expected that This is destroyed after all 'NativeEventListener's");
}

//======================================================================================================================
void NativeEventListeners::forEach(std::function<ListenerTraversalAction(NativeEventListener&)> func)
{
    for (auto& [id, listenerRef] : _listenersMap) {
        const auto traversalAction = func(listenerRef.get());
        if (traversalAction == ListenerTraversalAction::Break)
            break;
    }
}

//======================================================================================================================
NativeEventListenerId NativeEventListeners::_add(NativeEventListener& listener)
{
    const auto newListenerId = NativeEventListeners::_getNextListenerId();
    [[maybe_unused]] const auto [it, hasInserted] = _listenersMap.emplace(newListenerId, std::ref(listener));
    assert(hasInserted);

    return newListenerId;
}

//======================================================================================================================
void NativeEventListeners::_remove(NativeEventListenerId listenerId)
{
    [[maybe_unused]] const auto numErased = _listenersMap.erase(listenerId);
    assert(numErased > 0);
}

//======================================================================================================================
NativeEventListenerId NativeEventListeners::_getNextListenerId()
{
    static std::atomic<NativeEventListenerId> nextId = 1;
    return nextId.fetch_add(1);
}
