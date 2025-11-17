#pragma once

#include <Geometry2d/ContentTraits.h>

//======================================================================================================================
namespace render_2d {
    template <class Geometry>
    struct RenderableGeometry final {
        Geometry primitive;
        geometry_2d::ContentTraits<Geometry> contentTraits;
    };
}
