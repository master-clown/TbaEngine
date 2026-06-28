#include "OglGeometryBatchModifier.h"

#include "OglGeometryBatch.h"
#include "TypedOglBuffer.hpp"

#include <Common/NumericCast.hpp>
#include <Common/OverloadMultiplexor.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <OpenGlTexture/OpenGlTexture.h>
#include <TextureStorage/TextureStorage.h>

//======================================================================================================================
using namespace opengl_render_2d;

//======================================================================================================================
OglGeometryBatchModifier::OglGeometryBatchModifier(OglGeometryBatch& batch,
                                                   const texture_storage::TextureStorage& textureStorage)
    : _batch(batch)
    , _textureStorage(textureStorage)
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
    const auto& content = triangleGeometry.contentTraits.faceContent;
    const auto& texCoords = triangleGeometry.contentTraits.textureCoords;
    const auto vertex1Index = _addNewTriangleVertex(triangleGeometry.primitive.pt1, content, texCoords[0]);
    const auto vertex2Index = _addNewTriangleVertex(triangleGeometry.primitive.pt2, content, texCoords[1]);
    const auto vertex3Index = _addNewTriangleVertex(triangleGeometry.primitive.pt3, content, texCoords[2]);

    _batch._triangleIndexBuffer.getUnderlyingBuffer().append(vertex1Index);
    _batch._triangleIndexBuffer.getUnderlyingBuffer().append(vertex2Index);
    _batch._triangleIndexBuffer.getUnderlyingBuffer().append(vertex3Index);
}

//======================================================================================================================
auto OglGeometryBatchModifier::_addNewVertex(const geometry_2d::Point2d& pt,
                                             const content::Color& color) -> _VertexIndex
{
    const auto newVertexIndex = _batch._vertexBuffer.getUnderlyingBuffer().append(OglVertexInfo{
        .x = pt.x,
        .y = pt.y,
        .r = color.r,
        .g = color.g,
        .b = color.b,
        .a = color.a,
    });

    return numericCast<_VertexIndex>(newVertexIndex);
}

//======================================================================================================================
auto OglGeometryBatchModifier::_addNewTriangleVertex(const geometry_2d::Point2d& pt,
                                                     const content::Content& content,
                                                     const geometry_2d::TextureCoords& texCoords) -> _VertexIndex
{
    const auto newVertexIndex = std::visit(
        OverloadMultiplexor{
            [&](const content::Color& color) -> size_t {
                return _batch._vertexBuffer.getUnderlyingBuffer().append(OglVertexInfo{
                    .x = pt.x,
                    .y = pt.y,
                    .r = color.r,
                    .g = color.g,
                    .b = color.b,
                    .a = color.a,
                });
            },
            [&](const texture_storage::TextureId& texId) -> size_t {
                const auto& tex = _textureStorage.get(texId);
                assert(dynamic_cast<const opengl_texture::OpenGlTexture*>(&tex));

                const auto& oglTex = static_cast<const opengl_texture::OpenGlTexture&>(tex);
                const auto handleAsUint64 = oglTex.getOpenGlTextureHandle();
                return _batch._vertexBuffer.getUnderlyingBuffer().append(OglVertexInfo{
                    .x = pt.x,
                    .y = pt.y,
                    .handleLower4Bytes = numericCast<uint32>(handleAsUint64 & 0xFFFFFFFF),
                    .handleUpper4Bytes = numericCast<uint32>((handleAsUint64 >> 32) & 0xFFFFFFFF),
                    .u = texCoords.u,
                    .v = texCoords.v,
                });
            },
        },
        content);

    return numericCast<_VertexIndex>(newVertexIndex);
}
