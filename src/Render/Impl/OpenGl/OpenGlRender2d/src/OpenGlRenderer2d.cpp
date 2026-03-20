#include <OpenGlRender2d/OpenGlRenderer2d.h>

#include "OglGeometryBatch.h"
#include "ShaderPipeline.h"

#include <Common/NumericCast.hpp>
#include <Common/String.h>
#include <Content/Color.h>
#include <OpenGlApi/OpenGlApi.h>
#include <OpenGlContext/OpenGlContext.h>

#include <cassert>
#include <string_view>

//=====================================================================================================================
using namespace opengl_render_2d;

//=====================================================================================================================
static constexpr std::string_view basicVertexShader = R"(
#version 420 core

layout(location = 0) out vec4 outVertexColor;

layout(location = 0) in vec2 inVertexPosition; // NDC coordinate system
layout(location = 1) in vec4 inVertexColor;

void main() 
{
    gl_Position = vec4(inVertexPosition, 0.0, 1.0);
    outVertexColor = inVertexColor;
}
)";

//=====================================================================================================================
static constexpr std::string_view basicFragmentShader = R"(
#version 420 core

layout(location = 0) out vec4 fragmentColor;

layout(location = 0) in vec4 inVertexColor;

void main()
{
	fragmentColor = inVertexColor;
}
)";

//=====================================================================================================================
struct OpenGlRenderer2d::Pimpl final {
    uptr<ShaderPipeline> colorOnlyShaderPipeline;

    Pimpl()
        : colorOnlyShaderPipeline(makeUPtr<ShaderPipeline>(
              String{basicVertexShader},
              String{basicFragmentShader}))
    {
    }
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
void OpenGlRenderer2d::setBaseRenderResolution(const uint16 width, const uint16 height)
{
    glViewport(0, 0, numericCast<GLsizei>(width), numericCast<GLsizei>(height));
}

//=====================================================================================================================
void OpenGlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Point2d>& pt)
{
}

//=====================================================================================================================
void OpenGlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Line>& line)
{
}

//=====================================================================================================================
void OpenGlRenderer2d::render(const render_2d::RenderableGeometry<geometry_2d::Triangle>& triangle)
{
}

//=====================================================================================================================
uptr<render_2d::GeometryBatch> OpenGlRenderer2d::createGeometryBatch()
{
    return makeUPtr<OglGeometryBatch>();
}

//=====================================================================================================================
void OpenGlRenderer2d::renderGeometryBatch(const render_2d::GeometryBatch& geometryBatch)
{
    assert(dynamic_cast<const OglGeometryBatch*>(&geometryBatch));
    const auto& oglGeometryBatch = static_cast<const OglGeometryBatch&>(geometryBatch);

    const auto renderPrimitives = [&oglGeometryBatch](const OglIndexBuffer& indexBuffer,
                                                      const GLenum oglPrimitiveType) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.getEboId());
        glDrawElements(oglPrimitiveType,
                       indexBuffer.getUnderlyingBuffer().getItemCount(),
                       indexBuffer.getOglIndexType(),
                       0);
    };

    _pimpl->colorOnlyShaderPipeline->use();
    oglGeometryBatch.vao.use();

    renderPrimitives(oglGeometryBatch.pointIndexBuffer, GL_POINTS);
    renderPrimitives(oglGeometryBatch.lineIndexBuffer, GL_LINES);
    renderPrimitives(oglGeometryBatch.triangleIndexBuffer, GL_TRIANGLES);
}
