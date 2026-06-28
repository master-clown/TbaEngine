#include "OglTextureSampler.h"

#include "OglTextureHandles.h"

#include <OpenGlApi/ErrorCheck.h>
#include <OpenGlApi/OpenGlApi.h>
#include <Texture/TextureSamplingParameters.h>

#include <type_traits>

//======================================================================================================================
using opengl_texture::OglTextureSampler;

//======================================================================================================================
namespace {
    using OglAddressMode = GLint;
    constexpr OglAddressMode convertAddressMode(texture::TextureSamplingParameters::AddressMode) noexcept;

    using OglFiltering = GLint;
    constexpr OglFiltering convertMagnifyFiltering(texture::TextureSamplingParameters::Filtering) noexcept;
    constexpr OglFiltering convertMinifyFiltering(
        const texture::TextureSamplingParameters::Filtering pixelMode,
        const texture::TextureSamplingParameters::Filtering mipmapMode) noexcept;
}

//======================================================================================================================
static_assert(std::is_same_v<OglTextureSampler::OglSamplerId, GLuint>);

//======================================================================================================================
OglTextureSampler::OglTextureSampler(const texture::TextureSamplingParameters& params,
                                     OglTextureHandles& textureHandles)
    : _textureHandles(textureHandles)
    , _oglSamplerId([] {
        GLuint newId = 0;
        glCreateSamplers(1, &newId);
        opengl_api::checkOperationSuccess("glCreateSamplers(1, &newId)");
        return newId;
    }())
{
    glSamplerParameteri(_oglSamplerId, GL_TEXTURE_WRAP_S, convertAddressMode(params.addressModeU));
    glSamplerParameteri(_oglSamplerId, GL_TEXTURE_WRAP_T, convertAddressMode(params.addressModeV));
    glSamplerParameteri(_oglSamplerId, GL_TEXTURE_WRAP_R, convertAddressMode(params.addressModeW));
    glSamplerParameteri(_oglSamplerId,
                        GL_TEXTURE_MIN_FILTER,
                        convertMinifyFiltering(params.minifyNeighborFiltering, params.minifyMipmapFiltering));
    glSamplerParameteri(_oglSamplerId, GL_TEXTURE_MAG_FILTER, convertMagnifyFiltering(params.magnifyNeighborFiltering));
}

//======================================================================================================================
OglTextureSampler::~OglTextureSampler()
{
    // TODO: Is it OK to reset the current sampler this way, or it is better to do it through TexturingMgr?
    if (_textureHandles._getCurrentlyActiveSampler() == this)
        _textureHandles.setSamplerForAllTextures(nullptr);
}

//======================================================================================================================
auto OglTextureSampler::getOglSamplerId() const -> OglSamplerId
{
    return _oglSamplerId;
}

//======================================================================================================================
void OglTextureSampler::OnSamplerDestruction::operator()(const OglSamplerId& id) const noexcept
{
    glDeleteSamplers(1, &id);
    opengl_api::logOnOperationFailure(strFormat("glDeleteSamplers(id={})", id));
}

//======================================================================================================================
namespace {
    //==================================================================================================================
    constexpr OglAddressMode convertAddressMode(const texture::TextureSamplingParameters::AddressMode mode) noexcept
    {
        using En = texture::TextureSamplingParameters::AddressMode;

        switch (mode) {
        case En::Clamp: return GL_CLAMP_TO_EDGE;
        case En::MirroredRepeat: return GL_MIRRORED_REPEAT;
        case En::Repeat: return GL_REPEAT;
        }

        std::unreachable();
    }

    //==================================================================================================================
    constexpr OglFiltering convertMagnifyFiltering(const texture::TextureSamplingParameters::Filtering mode) noexcept
    {
        using En = texture::TextureSamplingParameters::Filtering;

        switch (mode) {
        case En::Nearest: return GL_NEAREST;
        case En::Linear: return GL_LINEAR;
        }

        std::unreachable();
    }

    //==================================================================================================================
    constexpr OglFiltering convertMinifyFiltering(
        const texture::TextureSamplingParameters::Filtering pixelMode,
        const texture::TextureSamplingParameters::Filtering mipmapMode) noexcept
    {
        using En = texture::TextureSamplingParameters::Filtering;

        if (pixelMode == En::Nearest)
            return mipmapMode == En::Nearest ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_LINEAR;

        if (pixelMode == En::Linear)
            return mipmapMode == En::Nearest ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR;

        std::unreachable();
    }
}
