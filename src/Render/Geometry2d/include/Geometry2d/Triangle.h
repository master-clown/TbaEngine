#pragma once

#include <Geometry2d/Point2d.h>
#include <Geometry2d/TextureCoords.h>

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
    // TODO: extract to separate headers (e.g. `ContentTraits.Triangle.h`)
    template <>
    struct ContentTraits<Triangle> final {
        content::Content faceContent = content::Color::white;

        // TODO: change this ad-hoc when the `libContent` is properly designed
        Array<TextureCoords, 3> textureCoords;
    };
}
