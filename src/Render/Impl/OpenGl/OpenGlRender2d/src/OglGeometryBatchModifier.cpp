#include "OglGeometryBatchModifier.h"

#include "OglGeometryBatch.h"
#include "TypedOglBuffer.hpp"

#include <Common/NumericCast.hpp>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>

//======================================================================================================================
using namespace opengl_render_2d;

//======================================================================================================================
OglGeometryBatchModifier::OglGeometryBatchModifier(OglGeometryBatch& batch)
    : _batch(batch)
{
}

//======================================================================================================================
void OglGeometryBatchModifier::clear()
{
    _batch._vertexBuffer.getUnderlyingBuffer().clear();

    _batch._triangleIndexBuffer.getUnderlyingBuffer().clear();
    _batch._lineIndexBuffer.getUnderlyingBuffer().clear();
    _batch._pointIndexBuffer.getUnderlyingBuffer().clear();
}

//======================================================================================================================
void OglGeometryBatchModifier::append(const render_2d::RenderableGeometry<geometry_2d::Point2d>& pt)
{
    const auto newVertexIndex = _addNewVertex(pt.primitive, pt.contentTraits.color);

    _batch._pointIndexBuffer.getUnderlyingBuffer().append(numericCast<OglIndexBuffer::Index>(newVertexIndex));
}

//======================================================================================================================
void OglGeometryBatchModifier::append(const render_2d::RenderableGeometry<geometry_2d::Line>& lineGeometry)
{
    const auto& color = lineGeometry.contentTraits.lineColor;
    const auto startVertexIndex = _addNewVertex(lineGeometry.primitive.startPt, color);
    const auto finalVertexIndex = _addNewVertex(lineGeometry.primitive.finalPt, color);

    _batch._lineIndexBuffer.getUnderlyingBuffer().append(startVertexIndex);
    _batch._lineIndexBuffer.getUnderlyingBuffer().append(finalVertexIndex);
}

//======================================================================================================================
void OglGeometryBatchModifier::append(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangleGeometry)
{
    const auto& color = std::get<content::Color>(triangleGeometry.contentTraits.faceContent);
    const auto vertex1Index = _addNewVertex(triangleGeometry.primitive.pt1, color);
    const auto vertex2Index = _addNewVertex(triangleGeometry.primitive.pt2, color);
    const auto vertex3Index = _addNewVertex(triangleGeometry.primitive.pt3, color);

    _batch._triangleIndexBuffer.getUnderlyingBuffer().append(vertex1Index);
    _batch._triangleIndexBuffer.getUnderlyingBuffer().append(vertex2Index);
    _batch._triangleIndexBuffer.getUnderlyingBuffer().append(vertex3Index);
}

//======================================================================================================================
OglIndexBuffer::Index OglGeometryBatchModifier::_addNewVertex(const geometry_2d::Point2d& pt,
                                                              const content::Color& color)
{
    const auto newVertexIndex = _batch._vertexBuffer.getUnderlyingBuffer().append(OglVertexInfo{
        .x = pt.x,
        .y = pt.y,
        .r = color.r,
        .g = color.g,
        .b = color.b,
        .a = color.a,
    });

    return numericCast<OglIndexBuffer::Index>(newVertexIndex);
}
