#include "OglVertexBuffer.h"

#include <OpenGlApi/ErrorCheck.h>
#include <OpenGlApi/OpenGlApi.h>

#include <type_traits>

//======================================================================================================================
using opengl_render_2d::OglVertexBuffer;
using opengl_render_2d::OglVertexInfo;
using opengl_render_2d::TypedOglBuffer;

//======================================================================================================================
void OglVertexBuffer::_staticAssertsOnTypedefs() noexcept
{
    static_assert(std::is_same_v<VboRawId, GLuint>);
    static_assert(std::is_same_v<VaoId, GLuint>);
}

//======================================================================================================================
OglVertexBuffer::OglVertexBuffer(const VaoId vaoId)
    : _vaoId(vaoId)
    , _buffer(OglBuffer::BufferExtendedCallback{[this] { _rebindVboToVao(); }})
{
    // TODO: assert(vao.isBinded());

    _rebindVboToVao();

    using AttribIdx = GLuint;
    using Normalization = decltype(GL_TRUE);

    static constexpr GLuint vboBindingPoint = 0;

    glEnableVertexArrayAttrib(_vaoId, AttribIdx{0});
    glVertexArrayAttribFormat(_vaoId, AttribIdx{0}, 2, GL_FLOAT, Normalization{GL_TRUE}, offsetof(OglVertexInfo, x));
    glVertexArrayAttribBinding(_vaoId, AttribIdx{0}, vboBindingPoint);

    glEnableVertexArrayAttrib(_vaoId, AttribIdx{1});
    glVertexArrayAttribFormat(_vaoId,
                              AttribIdx{1},
                              4,
                              GL_UNSIGNED_BYTE,
                              Normalization{GL_TRUE},
                              offsetof(OglVertexInfo, r));
    glVertexArrayAttribBinding(_vaoId, AttribIdx{1}, vboBindingPoint);

    glEnableVertexArrayAttrib(_vaoId, AttribIdx{2});
    glVertexArrayAttribIFormat(_vaoId,
                               AttribIdx{2},
                               2,
                               GL_UNSIGNED_INT,
                               offsetof(OglVertexInfo, handleLower4Bytes));
    glVertexArrayAttribBinding(_vaoId, AttribIdx{2}, vboBindingPoint);

    glEnableVertexArrayAttrib(_vaoId, AttribIdx{3});
    glVertexArrayAttribFormat(_vaoId, AttribIdx{3}, 2, GL_FLOAT, Normalization{GL_FALSE}, offsetof(OglVertexInfo, u));
    glVertexArrayAttribBinding(_vaoId, AttribIdx{3}, vboBindingPoint);
}

//======================================================================================================================
auto OglVertexBuffer::getVboId() const -> VboRawId
{
    return _buffer.getBufferRawId();
}

//======================================================================================================================
TypedOglBuffer<OglVertexInfo>& OglVertexBuffer::getUnderlyingBuffer()
{
    return _buffer;
}

//======================================================================================================================
const std::string_view& OglVertexBuffer::getVertexShaderText()
{
    static constexpr std::string_view vertexShader = R"(
#version 460 core

layout(location = 0) in vec2 inVertexPosition; // NDC coordinate system
layout(location = 1) in vec4 inVertexColor;
layout(location = 2) in uvec2 inTextureHandle;
layout(location = 3) in vec2 inTextureCoords;

layout(location = 0) out vec4 outVertexColor;
layout(location = 1) out flat uvec2 outTextureHandle;
layout(location = 2) out vec2 outTextureCoords;

void main() 
{
    gl_Position = vec4(inVertexPosition, 0.0, 1.0);
    outVertexColor = inVertexColor;
    outTextureHandle = inTextureHandle;
    outTextureCoords = inTextureCoords;
}
)";

    return vertexShader;
}

//======================================================================================================================
const std::string_view& OglVertexBuffer::getFragmentShaderText()
{
    static constexpr std::string_view fragmentShader = R"(
#version 460 core
#extension GL_ARB_bindless_texture : require

layout(location = 0) in vec4 inVertexColor;
layout(location = 1) in flat uvec2 inTextureHandle;
layout(location = 2) in vec2 inTextureCoords;

layout(location = 0) out vec4 fragmentColor;

void main()
{
    if(inTextureHandle == uvec2(0, 0)) {
        fragmentColor = inVertexColor;
        return;
    }

    sampler2D texSampler = sampler2D(inTextureHandle);
    fragmentColor = texture(texSampler, inTextureCoords);
}
)";

    return fragmentShader;
}

//======================================================================================================================
void OglVertexBuffer::_rebindVboToVao() const
{
    static constexpr GLuint vboBindingPoint = 0;

    glVertexArrayVertexBuffer(_vaoId, vboBindingPoint, _buffer.getBufferRawId(), 0, sizeof(OglVertexInfo));
    opengl_api::checkOperationSuccess("OglVertexBuffer::_rebindVboToVao(): glVertexArrayVertexBuffer()");
}
