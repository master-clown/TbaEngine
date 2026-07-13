#include "SdlGeometryBatchModifier.h"

#include "Details/PrimitiveVariant.h"
#include "SdlGeometryBatch.h"

#include <Common/OverloadMultiplexor.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <SdlTexture/SdlTexture.h>
#include <TextureStorage/TextureStorage.h>

#include <cassert>

//======================================================================================================================
using render_2d::RenderableGeometry;
using sdl_render_2d::SdlGeometryBatchModifier;
using sdl_render_2d::details::PrimitiveVariant;

//======================================================================================================================
namespace {
    // (0,0)
    //   . -- > U
    //   |
    // V v    x (1,1)
    using SdlTextureCoords = geometry_2d::TextureCoords;

    SdlTextureCoords makeSdlTextureCoords(const geometry_2d::TextureCoords& texCoords) noexcept
    {
        return SdlTextureCoords{.u = texCoords.u, .v = texCoords.v};
    }
}

//======================================================================================================================
SdlGeometryBatchModifier::SdlGeometryBatchModifier(SdlGeometryBatch& batch,
                                                   const texture_storage::TextureStorage& texStorage)
    : _batch(batch)
    , _textureStorage(texStorage)
{
}

//======================================================================================================================
void SdlGeometryBatchModifier::clear()
{
    _batch._getPrimitives().clear();
}

//======================================================================================================================
void SdlGeometryBatchModifier::append(const RenderableGeometry<geometry_2d::Point2d>& point)
{
    _batch._getPrimitives().push_back({
        .primitivePoints = {point.primitive},
        .color = point.contentTraits.color,
        .type = PrimitiveVariant::PrimitiveType::Point,
    });
}

//======================================================================================================================
void SdlGeometryBatchModifier::append(const RenderableGeometry<geometry_2d::Line>& line)
{
    const auto& startPt = line.primitive.startPt;
    const auto& finalPt = line.primitive.finalPt;

    _batch._getPrimitives().push_back({
        .primitivePoints = {startPt, finalPt},
        .color = line.contentTraits.lineColor,
        .type = PrimitiveVariant::PrimitiveType::Line,
    });
}

//======================================================================================================================
void SdlGeometryBatchModifier::append(const RenderableGeometry<geometry_2d::Triangle>& triangle)
{
    const auto& pt1 = triangle.primitive.pt1;
    const auto& pt2 = triangle.primitive.pt2;
    const auto& pt3 = triangle.primitive.pt3;

    PrimitiveVariant primitive{
        .primitivePoints = {pt1, pt2, pt3},
        .type = PrimitiveVariant::PrimitiveType::Triangle,
    };

    std::visit(
        OverloadMultiplexor{
            [&](const content::Color& color) mutable noexcept {
                primitive.color = color;
            },
            [&](const texture_storage::TextureId& texId) mutable {
                const auto& tex = _textureStorage.get(texId);
                assert(dynamic_cast<const sdl_texture::SdlTexture*>(&tex));

                const auto& sdlTexure = static_cast<const sdl_texture::SdlTexture&>(tex);
                primitive.sdlTexture = &sdlTexure.getSdlTexture();

                for (size_t iVertex = 0; iVertex < 3; ++iVertex)
                    primitive.primitiveTexCoords[iVertex] =
                        makeSdlTextureCoords(triangle.contentTraits.textureCoords[iVertex]);
            },
        },
        triangle.contentTraits.faceContent);

    _batch._getPrimitives().push_back(std::move(primitive));
}
