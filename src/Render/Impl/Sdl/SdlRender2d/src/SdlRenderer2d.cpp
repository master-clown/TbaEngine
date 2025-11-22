#include <SdlRender2d/SdlRenderer2d.h>

#include <Common/NumericCast.hpp>
#include <Common/OverloadMultiplexor.h>
#include <Common/Stl/Array.h>
#include <Common/String.h>
#include <Content/Color.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <Winsys/SdlWindow.h>

#include <SDL3/SDL.h>

//======================================================================================================================
// TODO: move to separate private headers
namespace {
    //==================================================================================================================
    auto makeSdlFColor(const content::Color& color) noexcept
    {
        static constexpr auto maxColorIntensity = content::Color::maxColorIntensity;

        return SDL_FColor{
            .r = numericCast<float>(color.r) / maxColorIntensity,
            .g = numericCast<float>(color.g) / maxColorIntensity,
            .b = numericCast<float>(color.b) / maxColorIntensity,
            .a = numericCast<float>(color.a) / maxColorIntensity,
        };
    }

    //==================================================================================================================
    struct SdlTriangle final {
        Array<SDL_Vertex, 3> sdlVertexes;

        void setFromTriangle(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangle)
        {
            const auto faceSdlFColor = makeSdlFColor(std::visit(
                OverloadMultiplexor{
                    [this](const content::Color& color) { return color; },
                    [](const auto&) {
                        throw std::runtime_error("Unsupported kind of Content for geometry_2d::Triangle");
                    },
                },
                triangle.contentTraits.faceContent));

            const auto makeSdlVertex = [&faceSdlFColor](const geometry_2d::Point2d& pt) noexcept {
                return SDL_Vertex{
                    .position = SDL_FPoint{
                        .x = numericCast<float>(pt.x),
                        .y = numericCast<float>(pt.y),
                    },
                    .color = faceSdlFColor,
                    .tex_coord = {0},
                };
            };

            sdlVertexes[0] = makeSdlVertex(triangle.primitive.pt1);
            sdlVertexes[1] = makeSdlVertex(triangle.primitive.pt2);
            sdlVertexes[2] = makeSdlVertex(triangle.primitive.pt3);
        }
    };
}

//=====================================================================================================================
struct sdl_render::SdlRenderer2d::Pimpl final {
    SDL_Renderer* renderer = nullptr;
    SdlTriangle sdlTriangle;

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
