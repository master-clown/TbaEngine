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
using render_2d::PrimitiveId;
using render_2d::RenderableGeometry;
using sdl_render_2d::SdlGeometryBatchModifier;
using sdl_render_2d::details::PrimitiveVariant;

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
namespace {
    template <typename Geometry>
    PrimitiveId registerNewPrimitive(auto& primIdToIdxMap, const auto& primIdx)
    {
        const auto newPrimitiveId = PrimitiveId::generate<Geometry>();
        primIdToIdxMap[newPrimitiveId] = numericCast<sdl_render_2d::SdlGeometryBatch::_PrimitiveIdx>(primIdx);

        return newPrimitiveId;
    }
}

//======================================================================================================================
PrimitiveId SdlGeometryBatchModifier::append(const RenderableGeometry<geometry_2d::Point2d>& point)
{
    auto& primitives = _batch._getPrimitives();
    primitives.push_back({
        .primitiveVertexes = {
            render_2d::VertexInfo{
                .coords = point.primitive,
                .color = point.contentTraits.color,
            },
        },
        .type = PrimitiveVariant::PrimitiveType::Point,
    });

    return registerNewPrimitive<geometry_2d::Point2d>(_batch._getPrimIdToIdxMap(), primitives.size() - 1);
}

//======================================================================================================================
PrimitiveId SdlGeometryBatchModifier::append(const RenderableGeometry<geometry_2d::Line>& line)
{
    const auto& startPt = line.primitive.startPt;
    const auto& finalPt = line.primitive.finalPt;

    auto& primitives = _batch._getPrimitives();
    primitives.push_back({
        .primitiveVertexes = {
            render_2d::VertexInfo{
                .coords = startPt,
                .color = line.contentTraits.lineColor,
            },
            render_2d::VertexInfo{
                .coords = finalPt,
                .color = line.contentTraits.lineColor,
            },
        },
        .type = PrimitiveVariant::PrimitiveType::Line,
    });

    return registerNewPrimitive<geometry_2d::Line>(_batch._getPrimIdToIdxMap(), primitives.size() - 1);
}

//======================================================================================================================
PrimitiveId SdlGeometryBatchModifier::append(const RenderableGeometry<geometry_2d::Triangle>& triangle)
{
    const auto& pt1 = triangle.primitive.pt1;
    const auto& pt2 = triangle.primitive.pt2;
    const auto& pt3 = triangle.primitive.pt3;

    PrimitiveVariant primitive{
        .primitiveVertexes = {
            render_2d::VertexInfo{.coords = pt1},
            render_2d::VertexInfo{.coords = pt2},
            render_2d::VertexInfo{.coords = pt3},
        },
        .type = PrimitiveVariant::PrimitiveType::Triangle,
    };

    std::visit(
        OverloadMultiplexor{
            [&](const content::Color& color) mutable noexcept {
                for (auto& vertexInfo : primitive.primitiveVertexes)
                    vertexInfo.color = color;
            },
            [&](const texture_storage::TextureId& texId) mutable {
                const auto& tex = _textureStorage.get(texId);
                assert(dynamic_cast<const sdl_texture::SdlTexture*>(&tex));

                const auto& sdlTexure = static_cast<const sdl_texture::SdlTexture&>(tex);
                primitive.sdlTexture = &sdlTexure.getSdlTexture();

                for (size_t iVertex = 0; iVertex < triangle.contentTraits.textureCoords.size(); ++iVertex)
                    primitive.primitiveVertexes[iVertex].textureCoords =
                        triangle.contentTraits.textureCoords[iVertex];
            },
        },
        triangle.contentTraits.faceContent);

    auto& primitives = _batch._getPrimitives();
    primitives.push_back(std::move(primitive));

    return registerNewPrimitive<geometry_2d::Triangle>(_batch._getPrimIdToIdxMap(), primitives.size() - 1);
}

//======================================================================================================================
void SdlGeometryBatchModifier::forEachPrimitiveVertex(const PrimitiveId primId,
                                                      const PrimitiveVertexAction& action)
{
    const auto primIdx = _batch._getPrimIdToIdxMap()[primId];
    auto& primitive = _batch._getPrimitives()[primIdx];

    const auto vertexCount = details::getVertexCountForPrimitiveType(primitive.type);
    for (uint8 iVertex = 0; iVertex < vertexCount; ++iVertex)
        action(iVertex, primitive.primitiveVertexes[iVertex]);
}
