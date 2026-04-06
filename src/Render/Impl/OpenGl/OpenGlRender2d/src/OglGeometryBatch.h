#pragma once

#include "OglIndexBuffer.h"
#include "OglVertexArrayObject.h"
#include "OglVertexBuffer.h"

#include <Common/Memory.h>
#include <Render2d/GeometryBatch.h>

//======================================================================================================================
namespace opengl_render_2d {
    class OglGeometryBatchModifier;
}

//======================================================================================================================
namespace opengl_render_2d {
    class OglGeometryBatch final : public render_2d::GeometryBatch {
    public:
        OglGeometryBatch();
        ~OglGeometryBatch();

        //--------------------------------------------------------------------------------------------------------------
        void modify(const std::function<void(render_2d::GeometryBatchModifier&)>&) override;

    private:
        // TODO: engage depth test in draw ordering
        static constexpr auto _defaultDepthValue = 0.5f;

        //--------------------------------------------------------------------------------------------------------------
        uptr<render_2d::GeometryBatchModifier> _modifier;

        //--------------------------------------------------------------------------------------------------------------
        friend class OpenGlRenderer2d;
        friend class OglGeometryBatchModifier;

        OglVertexArrayObject _vao;
        OglVertexBuffer _vertexBuffer;
        OglIndexBuffer _triangleIndexBuffer;
        OglIndexBuffer _lineIndexBuffer;
        OglIndexBuffer _pointIndexBuffer;
    };
}
