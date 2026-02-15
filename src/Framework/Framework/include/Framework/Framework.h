#pragma once

#include <Common/Memory.h>
#include <RendererContext/RendererType.h>

//======================================================================================================================
namespace event_sys {
    class EventMgr;
}

//======================================================================================================================
namespace input {
    class DeviceMgr;
}

//======================================================================================================================
namespace render {
    class Renderer;
}

//======================================================================================================================
namespace renderer_context {
    class RendererContextRaii;
}

//======================================================================================================================
namespace winsys {
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
        virtual uptr<render::Renderer> createRenderer(renderer_context::RendererContextRaii) = 0;

        //--------------------------------------------------------------------------------------------------------------
        static void enableStaticLogCategories(); // can be called by anyone at any time
    };
}
