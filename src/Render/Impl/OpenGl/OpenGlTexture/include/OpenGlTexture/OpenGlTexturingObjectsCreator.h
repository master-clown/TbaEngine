#pragma once

#include <Common/Memory.h>
#include <Texture/TexturingObjectsCreator.h>

//======================================================================================================================
namespace opengl_texture {
    class OglTextureHandles;
}

//======================================================================================================================
namespace opengl_texture {
    class OpenGlTexturingObjectsCreator final : public texture::TexturingObjectsCreator {
    public:
        OpenGlTexturingObjectsCreator();
        ~OpenGlTexturingObjectsCreator();

        uptr<texture::Texture> createTexture(const texture::TextureData&) override;
        uptr<texture::TextureSampler> createSampler(const texture::TextureSamplingParameters&) override;

    private:
        uptr<OglTextureHandles> _textureHandles;
    };
}
