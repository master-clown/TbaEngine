#pragma once

#include <Render2d/RenderableGeometry.h>

//======================================================================================================================
namespace geometry_2d {
    struct Point2d;
    struct Line;
    struct Triangle;
}

//======================================================================================================================
namespace render_2d {
    class GeometryBatch {
    public:
        virtual ~GeometryBatch();

        //--------------------------------------------------------------------------------------------------------------
        virtual void clear() = 0;

        //--------------------------------------------------------------------------------------------------------------
        // TODO: add bulk operations (to allocate the memory only once)
        virtual void add(const RenderableGeometry<geometry_2d::Point2d>&) = 0;
        virtual void add(const RenderableGeometry<geometry_2d::Line>&) = 0;
        virtual void add(const RenderableGeometry<geometry_2d::Triangle>&) = 0;
    };
}
