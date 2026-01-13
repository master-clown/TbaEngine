#pragma once

#include <Framework/Framework.h>

//======================================================================================================================
namespace sdl_framework {
    class SdlFramework final : public framework::Framework {
    public:
        SdlFramework();
        ~SdlFramework();

        event_sys::EventMgr& getEventMgr() override;
        winsys::WindowMgr& getWindowMgr() override;
        uptr<render::Renderer> createRenderer(render::RendererType, TargetWindow&) override;

    private:
        static uptr<render::Renderer> _createSdlRenderer(TargetWindow&);

    private:
        class SdlLibraryRaiiWrapper final {
        public:
            SdlLibraryRaiiWrapper();
            ~SdlLibraryRaiiWrapper();
        };

        SdlLibraryRaiiWrapper _sdlLibraryRaiiWrapper;
        uptr<event_sys::EventMgr> _sdlEventMgr;
        uptr<winsys::WindowMgr> _sdlWinMgr;
    };
}
