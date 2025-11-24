#pragma once

#include <Render2d/RenderableGeometry.h>

#include <Geometry2d/ScreenCoordinate.h>

//======================================================================================================================
namespace content {
    struct Color;
}

//======================================================================================================================
namespace geometry_2d {
    struct Point2d;
    struct Line;
    struct Triangle;
}

//======================================================================================================================
namespace render_2d {
    //==================================================================================================================
    class Renderer {
    public:
        virtual ~Renderer();

        // TODO: to separate interface? For both 2D and 3D
        virtual void clear(const content::Color&) = 0;
        virtual void finalizeRender() = 0;
        // end of TODO

        //--------------------------------------------------------------------------------------------------------------
        virtual void render(const RenderableGeometry<geometry_2d::Point2d>&) = 0;
        virtual void render(const RenderableGeometry<geometry_2d::Line>&) = 0;
        virtual void render(const RenderableGeometry<geometry_2d::Triangle>&) = 0;
    };
}
