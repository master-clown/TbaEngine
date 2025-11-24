#pragma once

#include <Render2d/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace sdl_render {
    //==================================================================================================================
    class SdlRenderer2d final : public render_2d::Renderer {
    public:
        SdlRenderer2d();
        ~SdlRenderer2d();

        void render(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        void render(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        void render(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        struct Pimpl;
        uptr<Pimpl> _pimpl;
    };
}
