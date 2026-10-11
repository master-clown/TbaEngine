#pragma once

#include <Common/Integers.h>
#include <Content/Color.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/TextureCoords.h>

//======================================================================================================================
namespace render_2d {
    struct VertexInfo final {
        geometry_2d::Point2d coords;
        // TODO: change this ad-hoc when the `libContent` is properly designed
        // (so the tex coords were part of content somehow)
        geometry_2d::TextureCoords textureCoords;
        content::Color color;
    };
}
