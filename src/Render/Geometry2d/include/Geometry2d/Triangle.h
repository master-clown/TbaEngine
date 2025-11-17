#pragma once

#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>

#include <Content/Content.h>

#include <optional>

//======================================================================================================================
namespace geometry_2d {
    //==================================================================================================================
    struct Triangle final {
        Point2d pt1;
        Point2d pt2;
        Point2d pt3;
    };

    //==================================================================================================================
    template <>
    struct ContentTraits<Triangle> final {
        content::Content faceContent = content::Color::white;

        std::optional<ContentTraits<Line>> edge12Traits;
        std::optional<ContentTraits<Line>> edge23Traits;
        std::optional<ContentTraits<Line>> edge31Traits;
    };
}
