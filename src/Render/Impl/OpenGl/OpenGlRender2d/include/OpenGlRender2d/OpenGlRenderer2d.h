#pragma once

#include <Render2d/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace opengl_context {
    class OpenGlContext;
}

//======================================================================================================================
namespace texture_storage {
    class TextureStorage;
}

//======================================================================================================================
namespace opengl_render_2d {
    //==================================================================================================================
    class OpenGlRenderer2d final : public render_2d::Renderer {
    public:
        OpenGlRenderer2d(opengl_context::OpenGlContext&, const texture_storage::TextureStorage&);
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
        const texture_storage::TextureStorage& _textureStorage;
        uptr<Pimpl> _pimpl;
    };
}
