#pragma once

#include <Common/Memory.h>
#include <Texture/TexturingMgr.h>

//======================================================================================================================
namespace sdl_texture {
    class SdlTexturingObjectsCreator;
}

//======================================================================================================================
struct SDL_Renderer;

//======================================================================================================================
namespace sdl_texture {
    class SdlTexturingMgr final : public texture::TexturingMgr {
    public:
        SdlTexturingMgr();
        ~SdlTexturingMgr();

        texture::TexturingObjectsCreator& getTexturingObjectsCreator() override;

        void setSdlRenderer(SDL_Renderer&);

    protected:
        void _setCurrentTextureSampler(TextureSamplerOrNull) override;

    private:
        SDL_Renderer* _sdlRenderer = nullptr;
        uptr<SdlTexturingObjectsCreator> _texturingObjectsCreator;
    };
}
