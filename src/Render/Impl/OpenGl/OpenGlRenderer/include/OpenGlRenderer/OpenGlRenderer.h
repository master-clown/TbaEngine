#pragma once

#include <Renderer/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace winsys {
    class Window;
}

//======================================================================================================================
namespace opengl_render {
    class OpenGlLibraryRaii;
    class WindowPreparer;
    class Context;
}

//======================================================================================================================
namespace opengl_render {
    //==================================================================================================================
    class OpenGlRenderer final : public render::Renderer {
    public:
        explicit OpenGlRenderer(uptr<WindowPreparer>);
        ~OpenGlRenderer();

        void clear(const content::Color&) override;
        void finalizeRender() override;

        render_2d::Renderer& get2dRenderer() override;
        render_3d::Renderer& get3dRenderer() override;

    private:
        uptr<OpenGlLibraryRaii> _openGlLibraryRaii;
        uptr<WindowPreparer> _windowPreparer;
        uptr<Context> _context;
        // uptr<render_2d::Renderer> _renderer2d;
    };
}
