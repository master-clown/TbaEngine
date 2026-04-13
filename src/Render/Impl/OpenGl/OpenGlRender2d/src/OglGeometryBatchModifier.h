#pragma once

#include "OglIndexBuffer.h"

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
namespace opengl_render_2d {
    class OglGeometryBatchModifier final : public render_2d::GeometryBatchModifier {
    public:
        explicit OglGeometryBatchModifier(OglGeometryBatch&);

        //--------------------------------------------------------------------------------------------------------------
        void clear() override;

        //--------------------------------------------------------------------------------------------------------------
        void append(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        void append(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        void append(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        using _VertexIndex = OglIndexBuffer::Index;
        _VertexIndex _addNewVertex(const geometry_2d::Point2d&, const content::Color&);

    private:
        OglGeometryBatch& _batch;
    };
}
