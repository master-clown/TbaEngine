#pragma once

#include <RendererContext/RendererPreconfigOptions.h>

//======================================================================================================================
namespace sdl_render_context {
    class SdlRenderPreconfigOptions : public renderer_context::RendererPreconfigOptions {
    public:
        renderer_context::RendererType getRendererType() const override;
    };
}
