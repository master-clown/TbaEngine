#include <TextureLoader/TextureLoader.h>

#include <Common/NumericCast.hpp>
#include <Texture/TextureData.h>

#include <cstring>
#include <filesystem>
#include <stdexcept>

//======================================================================================================================
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STBI_ONLY_TGA
#define STBI_ONLY_GIF
#include "stb_image.h"

//======================================================================================================================
using texture_loader::TextureLoader;

//======================================================================================================================
TextureLoader::TextureLoader()
{
    stbi_set_flip_vertically_on_load(true); // seems OK to call more than once
}

//======================================================================================================================
namespace {
    class StbImageRaii final {
    public:
        struct ImageInfo final {
            uint8* pixelData = nullptr;
            int width = 0;
            int height = 0;
            int channelCount = 0;

            size_t getPixelDataByteCount() const
            {
                return numericCast<size_t>(channelCount * width * height);
            }
        };

        explicit StbImageRaii(const String& filePath)
        {
            static constexpr int loadAllChannelsHint = 0;
            _imageInfo.pixelData = stbi_load(filePath.c_str(),
                                             &_imageInfo.width,
                                             &_imageInfo.height,
                                             &_imageInfo.channelCount,
                                             loadAllChannelsHint);

            if (!_imageInfo.pixelData)
                throw std::runtime_error(strFormat("Failed to load pixel data from texture file \"{}\": {}",
                                                   filePath,
                                                   stbi_failure_reason()));

            assert(_imageInfo.width > 0);
            assert(_imageInfo.height > 0);
            assert(_imageInfo.channelCount > 0);
        }

        ~StbImageRaii()
        {
            if (_imageInfo.pixelData)
                stbi_image_free(_imageInfo.pixelData);
        }

        const ImageInfo& getImageInfo() const
        {
            return _imageInfo;
        }

    private:
        ImageInfo _imageInfo;
    };
}

//======================================================================================================================
texture::TextureData TextureLoader::loadFromFile(const String& filePath)
{
    if (!std::filesystem::exists(filePath))
        throw std::runtime_error(strFormat("File \"{}\" does not exist", filePath));

    StbImageRaii stbImageRaii(filePath);
    const auto& imageInfo = stbImageRaii.getImageInfo();

    texture::TextureData textureData{
        .width = numericCast<uint32>(imageInfo.width),
        .height = numericCast<uint32>(imageInfo.height),
        .channelCount = numericCast<uint8>(imageInfo.channelCount),
    };

    const auto byteCount = imageInfo.getPixelDataByteCount();

    // TODO: avoid data duplication (it was more complicated to allow for custom deallocator)
    textureData.rawData.resize(byteCount);
    std::memcpy(&textureData.rawData[0], imageInfo.pixelData, byteCount);

    return textureData;
}
