#pragma once

#include <Winsys/WindowOptions.h>

#include <Common/Memory.h>
#include <Common/Stl/Optional.h>
#include <RendererContext/RendererType.h>

//======================================================================================================================
namespace renderer_context {
    class RendererContextRaii;
    class RendererContextCreator;
}

//======================================================================================================================
namespace winsys {
    class Window {
    public:
        Window(WindowOptions, uptr<renderer_context::RendererContextCreator>);
        virtual ~Window();

        //--------------------------------------------------------------------------------------------------------------
        renderer_context::RendererContextRaii createRendererContext();

        //--------------------------------------------------------------------------------------------------------------
        const WindowOptions& getWindowOptions() const;

    protected:
        Optional<renderer_context::RendererType> _getBindedRendererType() const;

    private:
        WindowOptions _windowOptions;
        uptr<renderer_context::RendererContextCreator> _rendererContextCreator;
    };
}
