#include <SdlRender2d/SdlRenderer2d.h>

#include "Details/SdlTriangle.h"

#include <Common/NumericCast.hpp>
#include <Common/String.h>
#include <Content/Color.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <SdlWinsys/SdlWindow.h>

#include <SDL3/SDL.h>

//=====================================================================================================================
struct sdl_render::SdlRenderer2d::Pimpl final {
    SDL_Renderer* renderer = nullptr;
    details::SdlTriangle sdlTriangle; // not thread-safe

    Pimpl(winsys::SdlWindow& sdlWindow)
    {
        renderer = SDL_CreateRenderer(&sdlWindow.getRawWindow(), nullptr);
        if (!renderer)
            throw std::runtime_error(String("Failed to create SDL renderer: ") + SDL_GetError());
    }

    ~Pimpl()
    {
        SDL_DestroyRenderer(renderer);
    }
};

//=====================================================================================================================
sdl_render::SdlRenderer2d::SdlRenderer2d(winsys::SdlWindow& sdlWindow)
    : _pimpl(makeUPtr<Pimpl>(sdlWindow))
{
}

//=====================================================================================================================
sdl_render::SdlRenderer2d::~SdlRenderer2d() = default;

//=====================================================================================================================
void sdl_render::SdlRenderer2d::clear(const content::Color& color)
{
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(_pimpl->renderer);
}

//=====================================================================================================================
void sdl_render::SdlRenderer2d::finalizeRender()
{
    SDL_RenderPresent(_pimpl->renderer);
}

//=====================================================================================================================
void sdl_render::SdlRenderer2d::setBaseRenderResolution(const geometry_2d::ScreenCoordinate width,
                                                        const geometry_2d::ScreenCoordinate height)
{
    if (!SDL_SetRenderLogicalPresentation(_pimpl->renderer,
                                          numericCast<int>(width),
                                          numericCast<int>(height),
                                          SDL_LOGICAL_PRESENTATION_STRETCH))
        throw std::runtime_error(strFormat(
            "Failed to set SDL renderer logical presentation (width={}, height={}): {}",
            width,
            height,
            SDL_GetError()));
}

//=====================================================================================================================
void sdl_render::SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Point2d>& pt)
{
    const auto& color = pt.contentTraits.color;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(_pimpl->renderer, numericCast<float>(pt.primitive.x), numericCast<float>(pt.primitive.y));
}

//=====================================================================================================================
void sdl_render::SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Line>& line)
{
    const auto& color = line.contentTraits.lineColor;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(_pimpl->renderer,
                   numericCast<float>(line.primitive.startPt.x),
                   numericCast<float>(line.primitive.startPt.y),
                   numericCast<float>(line.primitive.finalPt.x),
                   numericCast<float>(line.primitive.finalPt.y));
}

//=====================================================================================================================
void sdl_render::SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangle)
{
    _pimpl->sdlTriangle.setFromTriangle(triangle);

    SDL_RenderGeometry(_pimpl->renderer,
                       (SDL_Texture*)nullptr,
                       &_pimpl->sdlTriangle.sdlVertexes[0],
                       _pimpl->sdlTriangle.sdlVertexes.size(),
                       (int*)nullptr,
                       0);
}
