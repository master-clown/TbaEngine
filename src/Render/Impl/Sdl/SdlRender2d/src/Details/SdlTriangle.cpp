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
    auto makeSdlFColor(const content::Color& color) noexcept
    {
        static constexpr auto maxColorIntensity = content::Color::maxColorIntensity;

        return SDL_FColor{
            .r = numericCast<float>(color.r) / maxColorIntensity,
            .g = numericCast<float>(color.g) / maxColorIntensity,
            .b = numericCast<float>(color.b) / maxColorIntensity,
            .a = numericCast<float>(color.a) / maxColorIntensity,
        };
    }
}

//======================================================================================================================
void SdlTriangle::setFromPrimitiveVariant(const PrimitiveVariant& primitive)
{
    assert(primitive.type == PrimitiveVariant::PrimitiveType::Triangle);

    const auto faceSdlFColor = makeSdlFColor(primitive.mainColor);

    const auto makeSdlVertex = [this, &faceSdlFColor](const geometry_2d::Point2d& pt) noexcept {
        const auto sdlPt = transformToSdlPointFunc(pt);
        return SDL_Vertex{
            .position = sdlPt,
            .color = faceSdlFColor,
            .tex_coord = {0},
        };
    };

    const auto& coordArray = primitive.primitiveCoordArray;
    sdlVertexes[0] = makeSdlVertex({.x = coordArray[0], .y = coordArray[1]});
    sdlVertexes[1] = makeSdlVertex({.x = coordArray[2], .y = coordArray[3]});
    sdlVertexes[2] = makeSdlVertex({.x = coordArray[4], .y = coordArray[5]});
}
