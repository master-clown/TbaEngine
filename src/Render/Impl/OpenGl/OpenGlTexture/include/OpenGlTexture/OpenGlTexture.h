#pragma once

#include <OpenGlTexture/OpenGlTextureHandle.h>
#include <OpenGlTexture/OpenGlTextureId.h>

#include <Common/RaiiWrapper.h>
#include <Texture/Texture.h>

//======================================================================================================================
namespace texture {
    struct TextureData;
}

//======================================================================================================================
namespace opengl_texture {
    class OglTextureHandles;
}

//======================================================================================================================
namespace opengl_texture {
    class OpenGlTexture final : public texture::Texture {
    public:
        OpenGlTexture(const texture::TextureData&, OglTextureHandles&);
        ~OpenGlTexture();

        OpenGlTextureId getOpenGlTextureId() const;
        OpenGlTextureHandle getOpenGlTextureHandle() const;

    private:
        struct OnTextureDestruction final {
            void operator()(const OpenGlTextureId&) const noexcept;
        };
        using OpenGlTextureIdRaii = RaiiWrapper<OpenGlTextureId, OnTextureDestruction{}>;

        OglTextureHandles& _textureHandles;
        OpenGlTextureIdRaii _oglTextureId;
    };
}
