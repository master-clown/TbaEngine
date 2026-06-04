#pragma once

#include <Common/Integers.h>
#include <Common/Stl/Vector.h>

#include <cstddef>

//======================================================================================================================
namespace texture {
    struct TextureSamplingParameters final {
        enum class AddressMode : uint8 {
            Repeat,
            MirroredRepeat,
            Clamp,
        };

        enum class Filtering : uint8 {
            Nearest,
            Linear,
        };

        AddressMode addressModeU = AddressMode::Repeat;
        AddressMode addressModeV = AddressMode::Repeat;
        AddressMode addressModeW = AddressMode::Repeat;
        Filtering minifyNeighborFiltering = Filtering::Nearest;
        Filtering magnifyNeighborFiltering = Filtering::Nearest;
        Filtering minifyMipmapFiltering = Filtering::Linear;
    };
}
