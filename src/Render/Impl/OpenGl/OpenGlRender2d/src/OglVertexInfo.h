#pragma once

#include <Common/Integers.h>
#include <Geometry2d/ScreenCoordinate.h>

//======================================================================================================================
namespace opengl_render_2d {
    struct OglVertexInfo final {
        using NdcCoord = geometry_2d::ScreenCoordinate;

        // TODO: change this ad-hoc when the `libContent` is properly designed
        using TextureCoord = float;

        NdcCoord x = 0.0f;
        NdcCoord y = 0.0f;
        uint8 r = 0;
        uint8 g = 0;
        uint8 b = 0;
        uint8 a = 0;

        // TODO: change this ad-hoc when the `libContent` is properly designed
        uint32 handleLower4Bytes = 0;
        uint32 handleUpper4Bytes = 0;
        float u = 0.0;
        float v = 0.0;
    };
}
