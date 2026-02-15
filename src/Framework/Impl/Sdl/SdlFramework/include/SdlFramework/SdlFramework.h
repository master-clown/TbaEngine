#pragma once

#include <Framework/Framework.h>

//======================================================================================================================
namespace sdl_framework {
    class SdlFramework final : public framework::Framework {
    public:
        SdlFramework();
        ~SdlFramework();

        event_sys::EventMgr& getEventMgr() override;
        input::DeviceMgr& getDeviceMgr() override;
        winsys::WindowMgr& getWindowMgr() override;
        uptr<render::Renderer> createRenderer(renderer_context::RendererContextRaii) override;

    private:
        class SdlLibraryRaiiWrapper final {
        public:
            SdlLibraryRaiiWrapper();
            ~SdlLibraryRaiiWrapper();
        };

        SdlLibraryRaiiWrapper _sdlLibraryRaiiWrapper;
        uptr<event_sys::EventMgr> _sdlEventMgr;
        uptr<input::DeviceMgr> _sdlDeviceMgr;
        uptr<winsys::WindowMgr> _sdlWinMgr;
    };
}
