#pragma once

#include <Common/Memory.h>
#include <Renderer/RendererType.h>

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
        virtual uptr<render::Renderer> createRenderer(render::RendererType, TargetWindow&) = 0;

        //--------------------------------------------------------------------------------------------------------------
        static void enableStaticLogCategories(); // can be called by anyone at any time
    };
}
