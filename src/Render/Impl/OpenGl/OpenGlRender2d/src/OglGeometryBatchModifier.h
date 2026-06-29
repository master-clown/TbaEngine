#pragma once

#include "OglIndexBuffer.h"

#include <Content/Content.h>
#include <Render2d/GeometryBatchModifier.h>

//======================================================================================================================
namespace opengl_render_2d {
    class OglGeometryBatch;
}

//======================================================================================================================
namespace content {
    class Color;
}

//======================================================================================================================
// TODO: change this ad-hoc when the `libContent` is properly designed
namespace geometry_2d {
    struct TextureCoords;
}

//======================================================================================================================
namespace texture_storage {
    class TextureStorage;
}

//======================================================================================================================
namespace opengl_render_2d {
    class OglGeometryBatchModifier final : public render_2d::GeometryBatchModifier {
    public:
        OglGeometryBatchModifier(OglGeometryBatch&, const texture_storage::TextureStorage&);

        //--------------------------------------------------------------------------------------------------------------
        void clear() override;

        //--------------------------------------------------------------------------------------------------------------
        void append(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        void append(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        void append(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        using _VertexIndex = OglIndexBuffer::Index;
        _VertexIndex _addNewVertex(const geometry_2d::Point2d&, const content::Color&);

        // TODO: change this ad-hoc when the `libContent` is properly designed
        _VertexIndex _addNewTriangleVertex(const geometry_2d::Point2d&,
                                           const content::Content&,
                                           const geometry_2d::TextureCoords&);

    private:
        OglGeometryBatch& _batch;
        const texture_storage::TextureStorage& _textureStorage;
    };
}
