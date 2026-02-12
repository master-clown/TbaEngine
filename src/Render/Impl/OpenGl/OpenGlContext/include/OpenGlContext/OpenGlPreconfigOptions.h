#pragma once

#include <RendererContext/RendererPreconfigOptions.h>

//======================================================================================================================
namespace opengl_context {
    class OpenGlPreconfigOptions : public renderer_context::RendererPreconfigOptions {
    public:
        renderer_context::RendererType getRendererType() const override;
    };
}
