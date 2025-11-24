#pragma once

#include <Geometry2d/Point2d.h>

#include <Content/Color.h>

//======================================================================================================================
namespace geometry_2d {
    //==================================================================================================================
    struct Line final {
        Point2d startPt;
        Point2d finalPt;
    };

    //==================================================================================================================
    template <>
    struct ContentTraits<Line> final {
        content::Color lineColor = content::Color::white;
    };
}
