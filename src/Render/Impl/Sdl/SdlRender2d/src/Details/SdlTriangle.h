#pragma once

#include <Common/Stl/Array.h>
#include <Geometry2d/Point2d.h>
#include <Render2d/RenderableGeometry.h>

#include <functional>

#include <SDL3/SDL.h>

//======================================================================================================================
namespace sdl_render_2d::details {
    struct PrimitiveVariant;
}

//======================================================================================================================
namespace sdl_render_2d::details {
    //==================================================================================================================
    class SdlTriangle final {
    public:
        using SdlFPointFromPoint2d = std::function<SDL_FPoint(const geometry_2d::Point2d&)>;
        explicit SdlTriangle(SdlFPointFromPoint2d);

        //--------------------------------------------------------------------------------------------------------------
        using SdlVertexArray = Array<SDL_Vertex, 3>;
        SdlVertexArray& convertPrimitiveVariantToSdlVertexArray(const PrimitiveVariant&);

    private:
        SdlFPointFromPoint2d _transformToSdlPointFunc;
    };
}
