#pragma once

#include <Common/Integers.h>
#include <Common/Stl/Array.h>
#include <Content/Color.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/ScreenCoordinate.h>
#include <Geometry2d/TextureCoords.h>

//======================================================================================================================
// TODO: It is faster to store ptr to it instead of TextureId, but what if the texture is deleted?
// How the ptr would be changed to null? Is it probable at all?
struct SDL_Texture;

//======================================================================================================================
namespace sdl_render_2d::details {
    // Cache-friendly redundant struct to keep info of any primitive supported for rendering
    struct PrimitiveVariant final {
        static constexpr std::size_t maxVertexes = 3;

        using PrimitivePoints = Array<geometry_2d::Point2d, maxVertexes>;
        using PrimitiveTexCoords = Array<geometry_2d::TextureCoords, maxVertexes>;

        enum class PrimitiveType : uint8 {
            Point,
            Line,
            Triangle,
        };

        PrimitivePoints primitivePoints;
        PrimitiveTexCoords primitiveTexCoords;
        content::Color color;
        SDL_Texture* sdlTexture = nullptr;
        PrimitiveType type;
    };
}
