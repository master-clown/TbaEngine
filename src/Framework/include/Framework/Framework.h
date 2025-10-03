#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace winsys {
    class WindowMgr;
}

//----------------------------------------------------------------------------------------------------------------------
namespace app_event {
    class AppEventMgr;
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
        virtual app_event::AppEventMgr& getAppEventMgr() = 0;
        virtual audio::AudioMgr& getAudioMgr() = 0;
        virtual uptr<render::Renderer> createRenderer() = 0;
    };
}
