#pragma once

#include <RendererContext/RendererType.h>

//======================================================================================================================
namespace winsys {
    class Window;
}

//======================================================================================================================
namespace renderer_context {
    class RendererContext {
    public:
        virtual ~RendererContext();

        virtual RendererType getRendererType() const = 0;

        //--------------------------------------------------------------------------------------------------------------
        using TargetWindow = winsys::Window;
        void initContext(TargetWindow&);
        void freeContext();

        //--------------------------------------------------------------------------------------------------------------
        TargetWindow* getTargetWindow() const;

    private:
        virtual void _initContext() = 0;
        virtual void _freeContext() = 0;

    private:
        TargetWindow* _targetWindow = nullptr;
    };
}
