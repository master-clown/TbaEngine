#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace texture {
    class Texture;
    struct TextureData;
}

//======================================================================================================================
namespace texture {
    class TextureCreator {
    public:
        virtual ~TextureCreator();

        virtual uptr<Texture> create(TextureData) = 0;
    };
}
