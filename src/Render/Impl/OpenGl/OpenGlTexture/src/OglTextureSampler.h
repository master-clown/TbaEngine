#pragma once

#include <Common/Integers.h>
#include <Common/RaiiWrapper.h>
#include <Texture/TextureSampler.h>

//======================================================================================================================
namespace texture {
    struct TextureSamplingParameters;
}

//======================================================================================================================
namespace opengl_texture {
    class OglTextureHandles;
}

//======================================================================================================================
namespace opengl_texture {
    class OglTextureSampler final : public texture::TextureSampler {
    public:
        OglTextureSampler(const texture::TextureSamplingParameters&, OglTextureHandles&);
        ~OglTextureSampler();

        using OglSamplerId = uint32;
        OglSamplerId getOglSamplerId() const;

    private:
        struct OnSamplerDestruction final {
            void operator()(const OglSamplerId&) const noexcept;
        };
        using OglSamplerIdRaii = RaiiWrapper<OglSamplerId, OnSamplerDestruction{}>;

        OglTextureHandles& _textureHandles;
        OglSamplerIdRaii _oglSamplerId;
    };
}
