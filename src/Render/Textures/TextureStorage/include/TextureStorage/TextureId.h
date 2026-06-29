#pragma once

#include <Common/Integers.h>

//======================================================================================================================
namespace texture_storage {
    struct TextureId final {
        using Id = uint32;
        static constexpr Id noneTextureId = 0;

        Id id = noneTextureId;

        operator const Id&() const;
    };
}
