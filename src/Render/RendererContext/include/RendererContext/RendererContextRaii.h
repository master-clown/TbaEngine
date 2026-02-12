#pragma once

#include <RendererContext/RendererContext.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace winsys {
    class Window;
}

//======================================================================================================================
namespace renderer_context {
    class RendererContextRaii final {
    public:
        using TargetWindow = winsys::Window;
        explicit RendererContextRaii(uptr<RendererContext>, TargetWindow&);
        ~RendererContextRaii();

        //--------------------------------------------------------------------------------------------------------------
        RendererContextRaii(RendererContextRaii&&);
        RendererContextRaii& operator=(RendererContextRaii&&);

        //--------------------------------------------------------------------------------------------------------------
        RendererContext& operator*();
        const RendererContext& operator*() const;

        RendererContext* operator->();
        const RendererContext* operator->() const;

    private:
        uptr<RendererContext> _context;
    };
}
