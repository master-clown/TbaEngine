#pragma once

#include <Common/Memory.h>
#include <Texture/TexturingMgr.h>

//======================================================================================================================
namespace opengl_texture {
    class OglTextureHandles;
    class OglTexturingObjectsCreator;
}

//======================================================================================================================
namespace opengl_texture {
    class OpenGlTexturingMgr final : public texture::TexturingMgr {
    public:
        OpenGlTexturingMgr();
        ~OpenGlTexturingMgr();

        texture::TexturingObjectsCreator& getTexturingObjectsCreator() override;

    protected:
        void _setCurrentTextureSampler(TextureSamplerOrNull) override;

    private:
        uptr<OglTextureHandles> _textureHandles;
        uptr<OglTexturingObjectsCreator> _texturingObjectsCreator;
    };
}
