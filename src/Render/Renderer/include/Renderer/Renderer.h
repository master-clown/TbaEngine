#pragma once

#include <Common/Memory.h>
#include <RendererContext/RendererContextRaii.h>

//======================================================================================================================
namespace content {
    struct Color;
}

//======================================================================================================================
namespace render_2d {
    class Renderer;
}

//----------------------------------------------------------------------------------------------------------------------
namespace render_3d {
    class Renderer;
}

//======================================================================================================================
namespace texture {
    class TexturingMgr;
}

//======================================================================================================================
namespace texture_storage {
    class TextureStorage;
}

//======================================================================================================================
namespace render {
    //==================================================================================================================
    class Renderer {
    public:
        explicit Renderer(renderer_context::RendererContextRaii);
        virtual ~Renderer();

        // TODO: to separate interface? For both 2D and 3D, and here too
        virtual void clear(const content::Color&) = 0;
        virtual void finalizeRender() = 0;

        //--------------------------------------------------------------------------------------------------------------
        virtual render_2d::Renderer& get2dRenderer() = 0;
        virtual render_3d::Renderer& get3dRenderer() = 0;

        virtual texture::TexturingMgr& getTexturingMgr() = 0;

        //--------------------------------------------------------------------------------------------------------------
        renderer_context::RendererContext& getRendererContext();
        const renderer_context::RendererContext& getRendererContext() const;

        texture_storage::TextureStorage& getTextureStorage();
        const texture_storage::TextureStorage& getTextureStorage() const;

    private:
        renderer_context::RendererContextRaii _rendererContext;
        uptr<texture_storage::TextureStorage> _textureStorage;
    };
}
