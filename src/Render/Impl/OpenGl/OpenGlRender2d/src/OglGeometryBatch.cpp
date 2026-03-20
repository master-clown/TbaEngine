#include "OglGeometryBatch.h"

#include <Common/NumericCast.hpp>

//======================================================================================================================
using namespace opengl_render_2d;

//======================================================================================================================
OglGeometryBatch::OglGeometryBatch()
    : vao(OglVertexArrayObject::BindAfterCreation{})
    , vertexBuffer(vao.getRawId())
    , triangleIndexBuffer(vao.getRawId())
    , lineIndexBuffer(vao.getRawId())
    , pointIndexBuffer(vao.getRawId())
{
}

//======================================================================================================================
void OglGeometryBatch::clear()
{
    vertexBuffer.getUnderlyingBuffer().clear();
    triangleIndexBuffer.getUnderlyingBuffer().clear();
    lineIndexBuffer.getUnderlyingBuffer().clear();
}

//======================================================================================================================
void OglGeometryBatch::add(const render_2d::RenderableGeometry<geometry_2d::Point2d>& pt)
{
    const auto newVertexIndex = _addNewVertex(pt.primitive, pt.contentTraits.color);

    pointIndexBuffer.getUnderlyingBuffer().append(numericCast<OglIndexBuffer::Index>(newVertexIndex));
}

//======================================================================================================================
void OglGeometryBatch::add(const render_2d::RenderableGeometry<geometry_2d::Line>& lineGeometry)
{
    const auto& color = lineGeometry.contentTraits.lineColor;
    const auto startVertexIndex = _addNewVertex(lineGeometry.primitive.startPt, color);
    const auto finalVertexIndex = _addNewVertex(lineGeometry.primitive.finalPt, color);

    lineIndexBuffer.getUnderlyingBuffer().append(startVertexIndex);
    lineIndexBuffer.getUnderlyingBuffer().append(finalVertexIndex);
}

//======================================================================================================================
void OglGeometryBatch::add(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangleGeometry)
{
    const auto& color = std::get<content::Color>(triangleGeometry.contentTraits.faceContent);
    const auto vertex1Index = _addNewVertex(triangleGeometry.primitive.pt1, color);
    const auto vertex2Index = _addNewVertex(triangleGeometry.primitive.pt2, color);
    const auto vertex3Index = _addNewVertex(triangleGeometry.primitive.pt3, color);

    triangleIndexBuffer.getUnderlyingBuffer().append(vertex1Index);
    triangleIndexBuffer.getUnderlyingBuffer().append(vertex2Index);
    triangleIndexBuffer.getUnderlyingBuffer().append(vertex3Index);
}

//======================================================================================================================
OglIndexBuffer::Index OglGeometryBatch::_addNewVertex(const geometry_2d::Point2d& pt,
                                                      const content::Color& color)
{
    using NdcCoord = OglVertexInfo::NdcCoord;

    const auto newVertexIndex = vertexBuffer.getUnderlyingBuffer().append(OglVertexInfo{
        .x = pt.x,
        .y = pt.y,
        .r = color.r,
        .g = color.g,
        .b = color.b,
        .a = color.a,
    });

    return numericCast<OglIndexBuffer::Index>(newVertexIndex);
}
