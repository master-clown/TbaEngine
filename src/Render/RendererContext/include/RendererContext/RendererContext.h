#pragma once

//======================================================================================================================
namespace winsys {
    class Window;
}

//======================================================================================================================
namespace renderer_context {
    class RendererContext {
    public:
        virtual ~RendererContext();

        using TargetWindow = winsys::Window;
        virtual void initContext(TargetWindow&) = 0;
        virtual void freeContext() = 0;
    };
}
