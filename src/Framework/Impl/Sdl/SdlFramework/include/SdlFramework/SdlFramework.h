#pragma once

#include <Framework/Framework.h>

#include <AppEvent/AppEventMgr.h>
#include <Winsys/WindowMgr.h>

//======================================================================================================================
namespace framework {
    class SdlFramework final : public Framework {
    public:
        SdlFramework();
        ~SdlFramework();

        winsys::WindowMgr& getWindowMgr() override;
        app_event::AppEventMgr& getAppEventMgr() override;
        audio::AudioMgr& getAudioMgr() override;
        uptr<render::Renderer> createRenderer(render::RendererType,
                                              TargetWindow&) override;

    private:
        static uptr<render::Renderer> _createSdlRenderer(TargetWindow&);

    private:
        class SdlLibraryRaiiWrapper final {
        public:
            SdlLibraryRaiiWrapper();
            ~SdlLibraryRaiiWrapper();
        };

        SdlLibraryRaiiWrapper _sdlLibraryRaiiWrapper;
        uptr<winsys::WindowMgr> _sdlWinMgr;
        uptr<app_event::AppEventMgr> _sdlAppEventMgr;
    };
}
