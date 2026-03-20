#pragma once

#include <Render2d/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace opengl_context {
    class OpenGlContext;
}

//======================================================================================================================
namespace opengl_render_2d {
    //==================================================================================================================
    class OpenGlRenderer2d final : public render_2d::Renderer {
    public:
        explicit OpenGlRenderer2d(opengl_context::OpenGlContext&);
        ~OpenGlRenderer2d();

        void clear(const content::Color&) override;
        void finalizeRender() override;

        void setBaseRenderResolution(uint16 width, uint16 height) override;

        //--------------------------------------------------------------------------------------------------------------
        uptr<render_2d::GeometryBatch> createGeometryBatch() override;
        void renderGeometryBatch(const render_2d::GeometryBatch&) override;

    private:
        struct Pimpl;

        opengl_context::OpenGlContext& _openGlContext;
        uptr<Pimpl> _pimpl;
    };
}
