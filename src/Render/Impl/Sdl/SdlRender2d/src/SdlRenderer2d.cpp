#include <SdlRender2d/SdlRenderer2d.h>

#include "Details/PrimitiveVariant.h"
#include "Details/SdlTriangle.h"
#include "SdlGeometryBatch.h"

#include <Common/NumericCast.hpp>
#include <Common/String.h>
#include <Content/Color.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <SdlWinsys/SdlWindow.h>

#include <SDL3/SDL.h>

#include <cassert>

//=====================================================================================================================
using sdl_render_2d::SdlGeometryBatch;
using sdl_render_2d::SdlRenderer2d;
using sdl_render_2d::details::PrimitiveVariant;

//=====================================================================================================================
struct SdlRenderer2d::Pimpl final {
    struct ScreenSize final {
        uint16 width = 0;
        uint16 height = 0;
    };

    details::SdlTriangle sdlTriangle;
    SDL_Renderer* renderer = nullptr;
    ScreenSize currentScreenSize;

    Pimpl(sdl_winsys::SdlWindow& sdlWindow,
          details::SdlTriangle::SdlFPointFromPoint2d sdlFPointFromPoint2d)
        : sdlTriangle(std::move(sdlFPointFromPoint2d))
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
SdlRenderer2d::SdlRenderer2d(sdl_winsys::SdlWindow& sdlWindow, const texture_storage::TextureStorage& texStorage)
    : _textureStorage(texStorage)
    , _pimpl(makeUPtr<Pimpl>(sdlWindow,
                             [this](const geometry_2d::Point2d& pt) {
                                 const auto sdlPt = _toSdlScreenPoint2d(pt);
                                 return SDL_FPoint{.x = sdlPt.x, .y = sdlPt.y};
                             }))
{
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
uptr<render_2d::GeometryBatch> SdlRenderer2d::createGeometryBatch()
{
    return makeUPtr<SdlGeometryBatch>(_textureStorage);
}

//=====================================================================================================================
void SdlRenderer2d::renderGeometryBatch(const render_2d::GeometryBatch& geometryBatch)
{
    assert(dynamic_cast<const SdlGeometryBatch*>(&geometryBatch));
    const auto& sdlGeometryBatch = static_cast<const SdlGeometryBatch&>(geometryBatch);

    using PrimitiveType = PrimitiveVariant::PrimitiveType;

    for (const auto& primitive : sdlGeometryBatch._getPrimitives()) {
        if (primitive.type == PrimitiveType::Point)
            _renderAsPoint2d(primitive);
        else if (primitive.type == PrimitiveType::Line)
            _renderAsLine(primitive);
        else if (primitive.type == PrimitiveType::Triangle)
            _renderAsTriangle(primitive);
    }
}

//=====================================================================================================================
SDL_Renderer& SdlRenderer2d::getSdlRenderer()
{
    return const_cast<SDL_Renderer&>(static_cast<const SdlRenderer2d&>(*this).getSdlRenderer());
}

//=====================================================================================================================
const SDL_Renderer& SdlRenderer2d::getSdlRenderer() const
{
    assert(_pimpl->renderer);
    return *_pimpl->renderer;
}

//=====================================================================================================================
void SdlRenderer2d::_renderAsPoint2d(const PrimitiveVariant& primitive)
{
    assert(primitive.type == PrimitiveVariant::PrimitiveType::Point);

    const auto& color = primitive.color;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);

    const auto& pt = primitive.primitivePoints[0];
    const auto sdlPt = _toSdlScreenPoint2d({.x = pt.x, .y = pt.y});

    SDL_RenderPoint(_pimpl->renderer, sdlPt.x, sdlPt.y);
}

//=====================================================================================================================
void SdlRenderer2d::_renderAsLine(const PrimitiveVariant& primitive)
{
    assert(primitive.type == PrimitiveVariant::PrimitiveType::Line);

    const auto& color = primitive.color;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);

    const auto& pts = primitive.primitivePoints;
    const auto sdlStartPt = _toSdlScreenPoint2d({.x = pts[0].x, .y = pts[0].y});
    const auto sdlFinalPt = _toSdlScreenPoint2d({.x = pts[1].x, .y = pts[1].y});

    SDL_RenderLine(_pimpl->renderer, sdlStartPt.x, sdlStartPt.y, sdlFinalPt.x, sdlFinalPt.y);
}

//=====================================================================================================================
void SdlRenderer2d::_renderAsTriangle(const PrimitiveVariant& primitive)
{
    auto& sdlVertexArray = _pimpl->sdlTriangle.convertPrimitiveVariantToSdlVertexArray(primitive);

    using Indices = const int*;

    SDL_RenderGeometry(_pimpl->renderer,
                       primitive.sdlTexture,
                       &sdlVertexArray[0],
                       sdlVertexArray.size(),
                       (Indices) nullptr,
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
