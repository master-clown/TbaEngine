#pragma once

#include <Render2d/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindow;
}

//======================================================================================================================
namespace sdl_render {
    //==================================================================================================================
    class SdlRenderer2d final : public render_2d::Renderer {
    public:
        explicit SdlRenderer2d(sdl_winsys::SdlWindow&);
        ~SdlRenderer2d();

        void clear(const content::Color&) override;
        void finalizeRender() override;

        void setBaseRenderResolution(geometry_2d::ScreenCoordinate width,
                                     geometry_2d::ScreenCoordinate height) override;

        //--------------------------------------------------------------------------------------------------------------
        void render(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        void render(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        void render(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        struct Pimpl;
        uptr<Pimpl> _pimpl;
    };
}
