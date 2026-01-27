#pragma once

#include <Common/Memory.h>
#include <RendererType/RendererType.h>

//======================================================================================================================
namespace event_sys {
    class EventMgr;
}

//======================================================================================================================
namespace input {
    class DeviceMgr;
}

//----------------------------------------------------------------------------------------------------------------------
namespace render {
    class Renderer;
}

//----------------------------------------------------------------------------------------------------------------------
namespace winsys {
    class Window;
    class WindowMgr;

    struct WindowOptions;
}

//======================================================================================================================
namespace framework {
    class Framework {
    public:
        Framework();
        virtual ~Framework();

        virtual event_sys::EventMgr& getEventMgr() = 0;
        virtual input::DeviceMgr& getDeviceMgr() = 0;
        virtual winsys::WindowMgr& getWindowMgr() = 0;

        using TargetWindow = winsys::Window;
        virtual uptr<render::Renderer> createRenderer(renderer_type::RendererType, TargetWindow&) = 0;

        //==============================================================================================================
        struct WindowWithRenderer final {
            uptr<winsys::Window> window;
            uptr<render::Renderer> renderer;
        };

        WindowWithRenderer createWindowWithRenderer(winsys::WindowOptions, renderer_type::RendererType);

        //--------------------------------------------------------------------------------------------------------------
        static void enableStaticLogCategories(); // can be called by anyone at any time
    };
}
