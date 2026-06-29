#pragma once

#include <Common/Integers.h>
#include <Common/Stl/Vector.h>

#include <cstddef>

//======================================================================================================================
namespace texture {
    struct TextureData final {
        Vector<std::byte> rawData;
        uint32 width = 0;
        uint32 height = 0;
        uint8 channelCount = 0;
    };
}
