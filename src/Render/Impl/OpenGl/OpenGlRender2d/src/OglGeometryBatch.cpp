#include "OglGeometryBatch.h"

#include "OglGeometryBatchModifier.h"

#include <OpenGlApi/GpuOperationsCompletedEvent.h>

#include <cassert>

//======================================================================================================================
using namespace opengl_render_2d;

//======================================================================================================================
OglGeometryBatch::OglGeometryBatch(opengl_api::GpuOperationsCompletedEvent& gpuOperationsCompletedEvent)
    : _gpuOperationsCompletedEvent(gpuOperationsCompletedEvent)
    , _modifier(makeUPtr<OglGeometryBatchModifier>(*this))
    , _vao(OglVertexArrayObject::BindAfterCreation{})
    , _vertexBuffer(_vao.getRawId())
    , _triangleIndexBuffer(_vao.getRawId())
    , _lineIndexBuffer(_vao.getRawId())
    , _pointIndexBuffer(_vao.getRawId())
{
}

//======================================================================================================================
OglGeometryBatch::~OglGeometryBatch() = default;

//======================================================================================================================
void OglGeometryBatch::modify(const std::function<void(render_2d::GeometryBatchModifier&)>& modify)
{
    assert(_modifier);

    _gpuOperationsCompletedEvent.wait();

    modify(*_modifier);
}
