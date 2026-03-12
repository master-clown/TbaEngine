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
using sdl_render::SdlRenderer2d;

//=====================================================================================================================
struct SdlRenderer2d::Pimpl final {
    struct ScreenSize final {
        uint16 width = 0;
        uint16 height = 0;
    };

    SDL_Renderer* renderer = nullptr;
    ScreenSize currentScreenSize;
    details::SdlTriangle sdlTriangle; // not thread-safe

    Pimpl(sdl_winsys::SdlWindow& sdlWindow)
    {
        const auto& winOptions = sdlWindow.getWindowOptions();

        renderer = SDL_CreateRenderer(&sdlWindow.getRawWindow(), nullptr);
        if (!renderer)
            throw std::runtime_error(String("Failed to create SDL renderer: ") + SDL_GetError());

        currentScreenSize = {.width = winOptions.wndWidth, .height = winOptions.wndHeight};
    }

    ~Pimpl()
    {
        SDL_DestroyRenderer(renderer);
    }
};

//=====================================================================================================================
SdlRenderer2d::SdlRenderer2d(sdl_winsys::SdlWindow& sdlWindow)
    : _pimpl(makeUPtr<Pimpl>(sdlWindow))
{
    _pimpl->sdlTriangle.transformToSdlPointFunc = [this](const geometry_2d::Point2d& pt) {
        const auto sdlPt = _toSdlScreenPoint2d(pt);
        return SDL_FPoint{.x = sdlPt.x, .y = sdlPt.y};
    };
}

//=====================================================================================================================
SdlRenderer2d::~SdlRenderer2d() = default;

//=====================================================================================================================
void SdlRenderer2d::clear(const content::Color& color)
{
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(_pimpl->renderer);
}

//=====================================================================================================================
void SdlRenderer2d::finalizeRender()
{
    SDL_RenderPresent(_pimpl->renderer);
}

//=====================================================================================================================
void SdlRenderer2d::setBaseRenderResolution(const uint16 width, const uint16 height)
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

    _pimpl->currentScreenSize = {.width = width, .height = height};
}

//=====================================================================================================================
void SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Point2d>& pt)
{
    const auto& color = pt.contentTraits.color;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);

    const auto sdlPt = _toSdlScreenPoint2d(pt.primitive);
    SDL_RenderPoint(_pimpl->renderer, sdlPt.x, sdlPt.y);
}

//=====================================================================================================================
void SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Line>& line)
{
    const auto& color = line.contentTraits.lineColor;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);

    const auto sdlStartPt = _toSdlScreenPoint2d(line.primitive.startPt);
    const auto sdlFinalPt = _toSdlScreenPoint2d(line.primitive.finalPt);
    SDL_RenderLine(_pimpl->renderer, sdlStartPt.x, sdlStartPt.y, sdlFinalPt.x, sdlFinalPt.y);
}

//=====================================================================================================================
void SdlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangle)
{
    _pimpl->sdlTriangle.setFromTriangle(triangle);

    SDL_RenderGeometry(_pimpl->renderer,
                       (SDL_Texture*)nullptr,
                       &_pimpl->sdlTriangle.sdlVertexes[0],
                       _pimpl->sdlTriangle.sdlVertexes.size(),
                       (int*)nullptr,
                       0);
}

//=====================================================================================================================
auto SdlRenderer2d::_toSdlScreenPoint2d(const geometry_2d::Point2d& screenPt) const -> SdlScreenPoint2d
{
    return SdlScreenPoint2d{
        .x = _pimpl->currentScreenSize.width * (1.0f + screenPt.x) * 0.5f,
        // 0y of SDL and ours are opposite, hence minus sign
        .y = _pimpl->currentScreenSize.height * (1.0f - screenPt.y) * 0.5f,
    };
}
