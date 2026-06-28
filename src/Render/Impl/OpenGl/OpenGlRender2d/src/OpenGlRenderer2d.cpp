#include <OpenGlRender2d/OpenGlRenderer2d.h>

#include "OglGeometryBatch.h"
#include "OglVertexBuffer.h"
#include "ShaderPipeline.h"
#include "TypedOglBuffer.hpp"

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
struct OpenGlRenderer2d::Pimpl final {
    uptr<ShaderPipeline> colorOnlyShaderPipeline;

    Pimpl()
        : colorOnlyShaderPipeline(makeUPtr<ShaderPipeline>(
              String{OglVertexBuffer::getVertexShaderText()},
              String{OglVertexBuffer::getFragmentShaderText()}))
    {
    }
};

//=====================================================================================================================
OpenGlRenderer2d::OpenGlRenderer2d(opengl_context::OpenGlContext& openGlContext,
                                   const texture_storage::TextureStorage& textureStorage)
    : _openGlContext(openGlContext)
    , _textureStorage(textureStorage)
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
uptr<render_2d::GeometryBatch> OpenGlRenderer2d::createGeometryBatch()
{
    return makeUPtr<OglGeometryBatch>(_openGlContext.getGpuOperationsCompletedEvent(), _textureStorage);
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
    oglGeometryBatch._vao.use();

    renderPrimitives(oglGeometryBatch._pointIndexBuffer, GL_POINTS);
    renderPrimitives(oglGeometryBatch._lineIndexBuffer, GL_LINES);
    renderPrimitives(oglGeometryBatch._triangleIndexBuffer, GL_TRIANGLES);
}
