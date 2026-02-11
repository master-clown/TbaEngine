#pragma once

#include <Renderer/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace opengl_render {
    //==================================================================================================================
    class OpenGlRenderer final : public render::Renderer {
    public:
        explicit OpenGlRenderer(renderer_context::RendererContextRaii);
        ~OpenGlRenderer();

        void clear(const content::Color&) override;
        void finalizeRender() override;

        render_2d::Renderer& get2dRenderer() override;
        render_3d::Renderer& get3dRenderer() override;

    private:
        // uptr<render_2d::Renderer> _renderer2d;
    };
}
