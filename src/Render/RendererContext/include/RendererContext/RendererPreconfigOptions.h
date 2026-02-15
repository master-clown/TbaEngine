#pragma once

#include <RendererContext/RendererType.h>

//======================================================================================================================
namespace renderer_context {
    class RendererPreconfigOptions {
    public:
        virtual ~RendererPreconfigOptions();

        virtual RendererType getRendererType() const = 0;
    };
}
