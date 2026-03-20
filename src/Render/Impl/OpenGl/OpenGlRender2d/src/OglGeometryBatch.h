#pragma once

#include "OglBuffer.h"
#include "OglIndexBuffer.h"
#include "OglVertexArrayObject.h"
#include "OglVertexBuffer.h"
#include "TypedOglBuffer.hpp"

#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <Render2d/GeometryBatch.h>

//======================================================================================================================
namespace opengl_render_2d {
    class OglGeometryBatch final : public render_2d::GeometryBatch {
    public:
        OglGeometryBatch();

        //--------------------------------------------------------------------------------------------------------------
        void clear() override;

        //--------------------------------------------------------------------------------------------------------------
        void add(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        void add(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        void add(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        OglIndexBuffer::Index _addNewVertex(const geometry_2d::Point2d&, const content::Color&);

    private:
        // TODO: engage depth test in draw ordering
        static constexpr auto _defaultDepthValue = 0.5f;

        //--------------------------------------------------------------------------------------------------------------
        friend class OpenGlRenderer2d;

        OglVertexArrayObject vao;
        OglVertexBuffer vertexBuffer;
        OglIndexBuffer triangleIndexBuffer;
        OglIndexBuffer lineIndexBuffer;
        OglIndexBuffer pointIndexBuffer;
    };
}
