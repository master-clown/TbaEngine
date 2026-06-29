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
    class TexturingObjectsCreator {
    public:
        virtual ~TexturingObjectsCreator();

        virtual uptr<Texture> createTexture(const TextureData&) = 0;
        virtual uptr<TextureSampler> createSampler(const TextureSamplingParameters&) = 0;
    };
}
