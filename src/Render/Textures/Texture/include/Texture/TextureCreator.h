#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace texture {
    class Texture;
    struct TextureData;
    class TextureSampler;
    struct TextureSamplingParameters;
}

//======================================================================================================================
namespace texture {
    class TextureCreator {
    public:
        virtual ~TextureCreator();

        virtual uptr<Texture> create(const TextureData&) = 0;
        virtual uptr<TextureSampler> createSampler(const TextureSamplingParameters&) = 0;
    };
}
