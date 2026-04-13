#pragma once

#include <Geometry2d/ContentTraits.h>
#include <Geometry2d/ScreenCoordinate.h>

#include <Content/Color.h>

//======================================================================================================================
namespace geometry_2d {
    //==================================================================================================================
    struct Point2d final {
        ScreenCoordinate x = 0;
        ScreenCoordinate y = 0;
    };

    //==================================================================================================================
    template <>
    struct ContentTraits<Point2d> final {
        content::Color color = content::Color::white;
    };
}
