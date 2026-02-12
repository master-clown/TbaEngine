#pragma once

#include <Renderer/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindow;
}

//======================================================================================================================
namespace sdl_render {
    //==================================================================================================================
    class SdlRenderer final : public render::Renderer {
    public:
        // TODO: Window must be accessible from the context
        SdlRenderer(sdl_winsys::SdlWindow&, renderer_context::RendererContextRaii);
        ~SdlRenderer();

        void clear(const content::Color&) override;
        void finalizeRender() override;

        render_2d::Renderer& get2dRenderer() override;
        render_3d::Renderer& get3dRenderer() override;

    private:
        uptr<render_2d::Renderer> _renderer2d;
    };
}
