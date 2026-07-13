#include "SdlTriangle.h"

#include "PrimitiveVariant.h"

#include <Common/NumericCast.hpp>
#include <Content/Color.h>
#include <Geometry2d/Triangle.h>

#include <cassert>

//======================================================================================================================
using namespace sdl_render_2d::details;

//======================================================================================================================
namespace {
    //==================================================================================================================
    void setColorInSdlVertex(SDL_Vertex& sdlVertex,
                             const size_t iVertex,
                             const PrimitiveVariant& primitive) noexcept
    {
        static constexpr auto maxColorIntensity = content::Color::maxColorIntensity;

        const auto& color = primitive.color;
        sdlVertex.color = SDL_FColor{
            .r = numericCast<float>(color.r) / maxColorIntensity,
            .g = numericCast<float>(color.g) / maxColorIntensity,
            .b = numericCast<float>(color.b) / maxColorIntensity,
            .a = numericCast<float>(color.a) / maxColorIntensity,
        };
    }

    //==================================================================================================================
    void setTextureCoordsInSdlVertex(SDL_Vertex& sdlVertex,
                                     const size_t iVertex,
                                     const PrimitiveVariant& primitive) noexcept
    {
        const auto& texCoords = primitive.primitiveTexCoords[iVertex];
        sdlVertex.tex_coord.x = texCoords.u;
        sdlVertex.tex_coord.y = texCoords.v;
        sdlVertex.color.r = 1.0f;
        sdlVertex.color.g = 1.0f;
        sdlVertex.color.b = 1.0f;
        sdlVertex.color.a = 1.0f;
    }
}

//======================================================================================================================
SdlTriangle::SdlTriangle(SdlFPointFromPoint2d sdlFPointFromPoint2d)
    : _transformToSdlPointFunc(std::move(sdlFPointFromPoint2d))
{
    assert(_transformToSdlPointFunc);
}

//======================================================================================================================
auto SdlTriangle::convertPrimitiveVariantToSdlVertexArray(const PrimitiveVariant& primitive) -> SdlVertexArray&
{
    thread_local SdlVertexArray sdlVertexes;

    assert(primitive.type == PrimitiveVariant::PrimitiveType::Triangle);

    const auto& fillContentInfo = primitive.sdlTexture ? setTextureCoordsInSdlVertex : setColorInSdlVertex;

    const auto makeSdlVertex = [&](const size_t iVertex) noexcept {
        SDL_Vertex sdlVertex{
            .position = _transformToSdlPointFunc(primitive.primitivePoints[iVertex]),
        };
        fillContentInfo(sdlVertex, iVertex, primitive);

        return sdlVertex;
    };

    for (size_t iVertex = 0; iVertex < 3; ++iVertex)
        sdlVertexes[iVertex] = makeSdlVertex(iVertex);

    return sdlVertexes;
}
