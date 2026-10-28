#pragma once

#include <Render2d/GeometryBatchModifier.h>

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatch;
}

//======================================================================================================================
namespace texture_storage {
    class TextureStorage;
}

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatchModifier final : public render_2d::GeometryBatchModifier {
    public:
        SdlGeometryBatchModifier(SdlGeometryBatch&, const texture_storage::TextureStorage&);

        //--------------------------------------------------------------------------------------------------------------
        void clear() override;

        //--------------------------------------------------------------------------------------------------------------
        render_2d::PrimitiveId append(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        render_2d::PrimitiveId append(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        render_2d::PrimitiveId append(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

        //--------------------------------------------------------------------------------------------------------------
        void forEachPrimitiveVertex(render_2d::PrimitiveId, const PrimitiveVertexAction&) override;

    private:
        SdlGeometryBatch& _batch;
        const texture_storage::TextureStorage& _textureStorage;
    };
}
