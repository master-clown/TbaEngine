#pragma once

#include <Geometry2d/Point2d.h>

#include <Content/Color.h>

#include <optional>

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

        std::optional<ContentTraits<Point2d>> startPtTraits;
        std::optional<ContentTraits<Point2d>> finalPtTraits;
    };
}
