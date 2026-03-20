#pragma once

#include <Content/Color.h>
#include <Geometry2d/ScreenCoordinate.h>

#include <Common/Integers.h>
#include <Common/Stl/Array.h>

//======================================================================================================================
namespace sdl_render_2d::details {
    // Cache-friendly struct to keep info of any primitive supported for rendering
    struct PrimitiveVariant final {
        static constexpr auto maxAvailableCoordinates = 6;
        using PrimitiveCoordArray = Array<geometry_2d::ScreenCoordinate, maxAvailableCoordinates>;

        enum class PrimitiveType : uint8 {
            Point,
            Line,
            Triangle,
        };

        PrimitiveCoordArray primitiveCoordArray;
        content::Color mainColor;
        PrimitiveType type;
    };
}
