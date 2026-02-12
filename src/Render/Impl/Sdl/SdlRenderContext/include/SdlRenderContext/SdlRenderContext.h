#pragma once

#include <RendererContext/RendererContext.h>

//======================================================================================================================
namespace sdl_render_context {
    //==================================================================================================================
    class SdlRenderContext : public renderer_context::RendererContext {
    public:
        //--------------------------------------------------------------------------------------------------------------
        renderer_context::RendererType getRendererType() const override final;

    private:
        void _initContext() override;
        void _freeContext() override;
    };
}
