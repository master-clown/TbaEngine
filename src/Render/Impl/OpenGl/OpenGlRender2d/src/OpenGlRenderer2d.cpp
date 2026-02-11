#include <OpenGlRender2d/OpenGlRenderer2d.h>

#include <Common/NumericCast.hpp>
#include <Common/String.h>
#include <Content/Color.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <OpenGlContext/OpenGlApi.h>
#include <OpenGlContext/OpenGlContext.h>

//=====================================================================================================================
using opengl_render_2d::OpenGlRenderer2d;

//=====================================================================================================================
struct OpenGlRenderer2d::Pimpl final {
};

//=====================================================================================================================
OpenGlRenderer2d::OpenGlRenderer2d(opengl_context::OpenGlContext& openGlContext)
    : _openGlContext(openGlContext)
    , _pimpl(makeUPtr<Pimpl>())
{
}

//=====================================================================================================================
OpenGlRenderer2d::~OpenGlRenderer2d() = default;

//=====================================================================================================================
void OpenGlRenderer2d::clear(const content::Color& color)
{
    constexpr auto toFloat = [](const content::Color::ColorIntensity intensity) constexpr noexcept {
        return 1.0f * intensity / content::Color::maxColorIntensity;
    };

    glClearColor(toFloat(color.r), toFloat(color.g), toFloat(color.b), toFloat(color.a));
    glClear(GL_COLOR_BUFFER_BIT);
}

//=====================================================================================================================
void OpenGlRenderer2d::finalizeRender()
{
    _openGlContext.swapBuffers();
}

//=====================================================================================================================
void OpenGlRenderer2d::setBaseRenderResolution(const geometry_2d::ScreenCoordinate width,
                                               const geometry_2d::ScreenCoordinate height)
{
    glViewport(0, 0, numericCast<GLsizei>(width), numericCast<GLsizei>(height));
}

//=====================================================================================================================
void OpenGlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Point2d>& pt)
{
    /*
    const auto& color = pt.contentTraits.color;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(_pimpl->renderer, numericCast<float>(pt.primitive.x), numericCast<float>(pt.primitive.y));
    */
}

//=====================================================================================================================
void OpenGlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Line>& line)
{
    /*
    const auto& color = line.contentTraits.lineColor;
    SDL_SetRenderDrawColor(_pimpl->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(_pimpl->renderer,
                   numericCast<float>(line.primitive.startPt.x),
                   numericCast<float>(line.primitive.startPt.y),
                   numericCast<float>(line.primitive.finalPt.x),
                   numericCast<float>(line.primitive.finalPt.y));
    */
}

//=====================================================================================================================
void OpenGlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangle)
{
    /*
    _pimpl->sdlTriangle.setFromTriangle(triangle);

    SDL_RenderGeometry(_pimpl->renderer,
                       (SDL_Texture*)nullptr,
                       &_pimpl->sdlTriangle.sdlVertexes[0],
                       _pimpl->sdlTriangle.sdlVertexes.size(),
                       (int*)nullptr,
                       0);
    */
}
