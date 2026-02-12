#pragma once

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

        //--------------------------------------------------------------------------------------------------------------
        const renderer_context::RendererContext& getRendererContext() const;

    private:
        renderer_context::RendererContextRaii _rendererContext;
    };
}
