#pragma once

#include <Common/String.h>

//======================================================================================================================
namespace texture {
    struct TextureData;
}

//======================================================================================================================
namespace texture_loader {
    class TextureLoader final {
    public:
        TextureLoader();

        texture::TextureData loadFromFile(const String& filePath);
    };
}
