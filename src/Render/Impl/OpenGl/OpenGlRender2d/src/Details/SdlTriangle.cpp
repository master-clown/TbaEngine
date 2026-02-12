#include "SdlTriangle.h"

#include <Common/NumericCast.hpp>
#include <Common/OverloadMultiplexor.h>
#include <Content/Color.h>
#include <Geometry2d/Triangle.h>

#include <stdexcept>

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
void sdl_render::details::SdlTriangle::setFromTriangle(
    const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangle)
{
    const auto faceSdlFColor = makeSdlFColor(std::visit(
        OverloadMultiplexor{
            [this](const content::Color& color) { return color; },
            [](const auto&) {
                throw std::runtime_error("Unsupported kind of Content for geometry_2d::Triangle");
            },
        },
        triangle.contentTraits.faceContent));

    const auto makeSdlVertex = [&faceSdlFColor](const geometry_2d::Point2d& pt) noexcept {
        return SDL_Vertex{
            .position = SDL_FPoint{
                .x = numericCast<float>(pt.x),
                .y = numericCast<float>(pt.y),
            },
            .color = faceSdlFColor,
            .tex_coord = {0},
        };
    };

    sdlVertexes[0] = makeSdlVertex(triangle.primitive.pt1);
    sdlVertexes[1] = makeSdlVertex(triangle.primitive.pt2);
    sdlVertexes[2] = makeSdlVertex(triangle.primitive.pt3);
}
