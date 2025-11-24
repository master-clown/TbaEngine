#include <SdlRender2d/SdlRenderer2d.h>

#include <SDL3/SDL.h>

//==================================================================================================================
struct sdl_render::SdlRenderer2d::Pimpl final {
};

//==================================================================================================================
sdl_render::SdlRenderer2d::SdlRenderer2d() = default;

//==================================================================================================================
sdl_render::SdlRenderer2d::~SdlRenderer2d() = default;

//==================================================================================================================
void sdl_render::SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Point2d>& pt)
{
}

//==================================================================================================================
void sdl_render::SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Line>& line)
{
}

//==================================================================================================================
void sdl_render::SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangle)
{
}
