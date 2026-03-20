#pragma once

#include <Common/Integers.h>
#include <Geometry2d/ScreenCoordinate.h>

//======================================================================================================================
namespace opengl_render_2d {
    struct OglVertexInfo final {
        using NdcCoord = geometry_2d::ScreenCoordinate;

        NdcCoord x = 0.0f;
        NdcCoord y = 0.0f;
        uint8 r = 0;
        uint8 g = 0;
        uint8 b = 0;
        uint8 a = 0;
    };
}
