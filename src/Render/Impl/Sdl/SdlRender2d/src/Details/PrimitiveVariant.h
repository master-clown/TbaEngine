#pragma once

#include <Common/Stl/Array.h>
#include <Render2d/PrimitiveType.h>
#include <Render2d/VertexInfo.h>

//======================================================================================================================
// TODO: It is faster to store ptr to it instead of TextureId, but what if the texture is deleted?
// How the ptr would be changed to null? Is it probable at all?
struct SDL_Texture;

//======================================================================================================================
namespace sdl_render_2d::details {
    // Cache-friendly redundant struct to keep info of any primitive supported for rendering
    struct PrimitiveVariant final {
        static constexpr std::size_t maxVertexes = 3;
        using PrimitiveVertexes = Array<render_2d::VertexInfo, maxVertexes>;

        PrimitiveVertexes primitiveVertexes;
        SDL_Texture* sdlTexture = nullptr;
        render_2d::PrimitiveType type;
    };
}
