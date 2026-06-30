#pragma once

#include <Common/Memory.h>
#include <Texture/TexturingMgr.h>

//======================================================================================================================
namespace sdl_texture {
    class SdlTexturingObjectsCreator;
}

//======================================================================================================================
namespace sdl_texture {
    class SdlTexturingMgr final : public texture::TexturingMgr {
    public:
        SdlTexturingMgr();
        ~SdlTexturingMgr();

        texture::TexturingObjectsCreator& getTexturingObjectsCreator() override;

    protected:
        void _setCurrentTextureSampler(TextureSamplerOrNull) override;

    private:
        uptr<SdlTexturingObjectsCreator> _texturingObjectsCreator;
    };
}
