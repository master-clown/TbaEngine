#pragma once

#include <Common/Memory.h>
#include <Renderer/RendererType.h>

//======================================================================================================================
namespace winsys {
    class Window;
    class WindowMgr;
}

//----------------------------------------------------------------------------------------------------------------------
namespace event_sys {
    class EventMgr;
}

//----------------------------------------------------------------------------------------------------------------------
namespace audio {
    class AudioMgr;
}

//----------------------------------------------------------------------------------------------------------------------
namespace render {
    class Renderer;
}

//======================================================================================================================
namespace framework {
    class Framework {
    public:
        virtual ~Framework();

        virtual winsys::WindowMgr& getWindowMgr() = 0;
        virtual event_sys::EventMgr& getEventMgr() = 0;
        virtual audio::AudioMgr& getAudioMgr() = 0;

        using TargetWindow = winsys::Window;
        virtual uptr<render::Renderer> createRenderer(render::RendererType, TargetWindow&) = 0;
    };
}
