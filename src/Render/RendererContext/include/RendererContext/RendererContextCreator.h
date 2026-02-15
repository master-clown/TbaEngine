#pragma once

#include <RendererContext/RendererType.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace renderer_context {
    class RendererContextRaii;
    class RendererPreconfigOptions;
}

//======================================================================================================================
namespace winsys {
    class Window;
}

//======================================================================================================================
namespace renderer_context {
    class RendererContextCreator {
    public:
        explicit RendererContextCreator(uptr<RendererPreconfigOptions>);
        virtual ~RendererContextCreator();

        //--------------------------------------------------------------------------------------------------------------
        virtual void configureBeforeWindowCreation() = 0;

        using TargetWindow = winsys::Window;
        virtual RendererContextRaii createRendererContext(TargetWindow&) = 0;

        //--------------------------------------------------------------------------------------------------------------
        RendererType getRendererType() const;
        const RendererPreconfigOptions& getRendererPreconfigOptions() const;

    private:
        uptr<RendererPreconfigOptions> _rendererPreconfigOptions;
    };
}
