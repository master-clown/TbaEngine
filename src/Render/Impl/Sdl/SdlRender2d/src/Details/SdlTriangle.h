#pragma once

#include <Common/Stl/Array.h>
#include <Render2d/RenderableGeometry.h>

#include <SDL3/SDL.h>

//======================================================================================================================
namespace geometry_2d {
    struct Triangle;
}

//======================================================================================================================
namespace sdl_render::details {
    //==================================================================================================================
    struct SdlTriangle final {
        Array<SDL_Vertex, 3> sdlVertexes;

        void setFromTriangle(const render_2d::RenderableGeometry<geometry_2d::Triangle>&);
    };
}
