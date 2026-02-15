#pragma once

#include <Winsys/Window.h>

#include <Common/Memory.h>
#include <Common/Stl/Optional.h>
#include <RendererContext/RendererPreconfigOptions.h>

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners;
}

//======================================================================================================================
namespace winsys {
    class WindowMgr {
    public:
        explicit WindowMgr(event_sys::NativeEventListeners&);
        virtual ~WindowMgr();

        //--------------------------------------------------------------------------------------------------------------
        struct CreateWindowOptions final {
            WindowOptions winOptions;
            Optional<uptr<renderer_context::RendererPreconfigOptions>> rendererPreconfigOptions = {};
        };

        virtual uptr<Window> createWindow(CreateWindowOptions) = 0;

        //--------------------------------------------------------------------------------------------------------------
        event_sys::NativeEventListeners& getNativeEventListeners();

    private:
        event_sys::NativeEventListeners& _nativeEventListeners;
    };
}
