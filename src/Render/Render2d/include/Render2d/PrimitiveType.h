#pragma once

#include <Common/Integers.h>

//======================================================================================================================
namespace render_2d {
    //==================================================================================================================
    enum class PrimitiveType : uint8 {
        Point = 1,
        Line = 2,
        Triangle = 3,
    };

    //==================================================================================================================
    constexpr std::size_t vertexCountForPrimitiveType(const PrimitiveType primType) noexcept
    {
        return static_cast<std::size_t>(primType);
    }
}
