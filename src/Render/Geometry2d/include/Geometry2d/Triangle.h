#pragma once

#include <Geometry2d/Point2d.h>

#include <Common/Stl/Array.h>
#include <Content/Content.h>

//======================================================================================================================
namespace geometry_2d {
    //==================================================================================================================
    struct Triangle final {
        Point2d pt1;
        Point2d pt2;
        Point2d pt3;
    };

    //==================================================================================================================
    // TODO: change this ad-hoc when the `libContent` is properly designed
    struct TextureCoords final {
        float u = 0.0;
        float v = 0.0;
    };

    //==================================================================================================================
    // TODO: extract to separate headers (e.g. `ContentTraits.Triangle.h`)
    template <>
    struct ContentTraits<Triangle> final {
        content::Content faceContent = content::Color::white;

        // TODO: change this ad-hoc when the `libContent` is properly designed
        Array<TextureCoords, 3> textureCoords;
    };
}
