#include <OpenGlTexture/OpenGlTexture.h>

#include "OglTextureHandles.h"

#include <Common/NumericCast.hpp>
#include <OpenGlApi/ErrorCheck.h>
#include <OpenGlApi/OpenGlApi.h>
#include <Texture/TextureData.h>

#include <bit>

//======================================================================================================================
using opengl_texture::OpenGlTexture;
using opengl_texture::OpenGlTextureHandle;
using opengl_texture::OpenGlTextureId;

//======================================================================================================================
namespace {
    //==================================================================================================================
    using OglSizedPixelFormat = GLint;
    using OglPixelFormat = GLint;
    constexpr std::pair<OglSizedPixelFormat, OglPixelFormat> pixelFormatFromNumOfChannels(uint8 numOfChannels) noexcept;

    //==================================================================================================================
    template <class Uint>
    constexpr int fastLog2(Uint x) noexcept
        requires std::is_unsigned_v<Uint>;

    //==================================================================================================================
    constexpr int numOfMipmapLevelsFromTextureSize(uint32 width, uint32 height) noexcept;
}

//======================================================================================================================
OpenGlTexture::OpenGlTexture(const texture::TextureData& textureData, OglTextureHandles& textureHandles)
    : _textureHandles(textureHandles)
    , _oglTextureId([] {
        GLuint newId = 0;
        glCreateTextures(GL_TEXTURE_2D, 1, &newId);
        opengl_api::checkOperationSuccess("glCreateTextures(GL_TEXTURE_2D, 1, &newId)");
        return newId;
    }())
{
    using MipmapLevel = GLint;
    using TexelOffset = GLint;
    using BorderParam = GLint;
    using PixelDataType = GLenum;

    const MipmapLevel numOfMipmapLevels = numOfMipmapLevelsFromTextureSize(textureData.width, textureData.height);
    const auto [sizedPixelFormat, pixelFormat] = pixelFormatFromNumOfChannels(textureData.channelCount);

    glTextureStorage2D(_oglTextureId,
                       numOfMipmapLevels,
                       sizedPixelFormat,
                       textureData.width,
                       textureData.height);
    opengl_api::checkOperationSuccess(strFormat("glTextureStorage2D(_oglTextureId={}, numOfMipmapLevels={})",
                                                _oglTextureId.getUnderlying(),
                                                numOfMipmapLevels));

    glTextureSubImage2D(_oglTextureId,
                        MipmapLevel{0},
                        TexelOffset{0},
                        TexelOffset{0},
                        numericCast<GLsizei>(textureData.width),
                        numericCast<GLsizei>(textureData.height),
                        pixelFormat,
                        PixelDataType{GL_UNSIGNED_BYTE},
                        &textureData.rawData[0]);
    opengl_api::checkOperationSuccess(strFormat("glTextureSubImage2D(_oglTextureId={})",
                                                _oglTextureId.getUnderlying()));

    // TODO: generate mipmaps? Or control it with a parameter?
    glGenerateTextureMipmap(_oglTextureId);
    opengl_api::checkOperationSuccess(strFormat("glGenerateTextureMipmap(_oglTextureId={})",
                                                _oglTextureId.getUnderlying()));

    _textureHandles.addForTexture(_oglTextureId);
}

//======================================================================================================================
OpenGlTexture::~OpenGlTexture()
{
    _textureHandles.removeForTexture(_oglTextureId);
}

//======================================================================================================================
OpenGlTextureId OpenGlTexture::getOpenGlTextureId() const
{
    return _oglTextureId;
}

//======================================================================================================================
OpenGlTextureHandle OpenGlTexture::getOpenGlTextureHandle() const
{
    return _textureHandles.getHandle(_oglTextureId);
}

//======================================================================================================================
void OpenGlTexture::OnTextureDestruction::operator()(const OpenGlTextureId& id) const noexcept
{
    glDeleteTextures(1, &id);
    opengl_api::logOnOperationFailure(strFormat("glDeleteTextures(id={})", id));
}

//======================================================================================================================
namespace {
    //==================================================================================================================
    using OglSizedPixelFormat = GLint;
    using OglPixelFormat = GLint;

    constexpr std::pair<OglSizedPixelFormat, OglPixelFormat> pixelFormatFromNumOfChannels(
        const uint8 numOfChannels) noexcept
    {
        switch (numOfChannels) {
        case 1: return {GL_R8, GL_RED};
        case 2: return {GL_RG8, GL_RG};
        case 3: return {GL_RGB8, GL_RGB};
        case 4: return {GL_RGBA8, GL_RGBA};
        default: break;
        }

        std::unreachable();
    }

    //==================================================================================================================
    template <class Uint>
    constexpr int fastLog2(const Uint number) noexcept
        requires std::is_unsigned_v<Uint>
    {
        return std::bit_width(number) - 1;
    }

    //==================================================================================================================
    constexpr int numOfMipmapLevelsFromTextureSize(const uint32 width, const uint32 height) noexcept
    {
        return fastLog2(std::max(width, height)) + 1;
    }
}
