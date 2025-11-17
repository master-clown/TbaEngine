#pragma once

#include <Renderer/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace render_2d {
    class Renderer;
}

//======================================================================================================================
namespace sdl_render {
    //==================================================================================================================
    class SdlRenderer final : public render::Renderer {
    public:
        SdlRenderer();
        ~SdlRenderer();

        void clear() override;
        void finalizeRender() override;

        render_2d::Renderer& get2dRenderer() override;
        render_3d::Renderer& get3dRenderer() override;

    private:
        uptr<render_2d::Renderer> _renderer2d;
    };
}
