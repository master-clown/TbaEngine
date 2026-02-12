#pragma once

#include <RendererContext/RendererContextCreator.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace renderer_context {
    class RendererContext;
}

//======================================================================================================================
namespace sdl_winsys {
    class SdlRenderContextCreator final : public renderer_context::RendererContextCreator {
    public:
        explicit SdlRenderContextCreator(uptr<renderer_context::RendererPreconfigOptions>);
        ~SdlRenderContextCreator();

        void configureBeforeWindowCreation() override;
        renderer_context::RendererContextRaii createRendererContext(TargetWindow&) override;

    private:
        uptr<renderer_context::RendererContext> _contextToCreate;
    };
}
