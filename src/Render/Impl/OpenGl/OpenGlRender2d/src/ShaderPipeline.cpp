#include "ShaderPipeline.h"

#include <OpenGlApi/OpenGlApi.h>

#include <type_traits>

//======================================================================================================================
using opengl_render_2d::ShaderPipeline;

//======================================================================================================================
void ShaderPipeline::_staticAssertsOnTypedefs() noexcept
{
    static_assert(std::is_same_v<OglEnum, GLenum>);
    static_assert(std::is_same_v<ShaderId, GLuint>);
    static_assert(std::is_same_v<ProgramId, GLuint>);
    static_assert(std::is_same_v<UniformLocation, GLint>);
}

//======================================================================================================================
ShaderPipeline::ShaderPipeline(const String& vertexShaderCode, const String& fragmentShaderCode)
{
    const auto vertexShaderId = _createShader(vertexShaderCode, GL_VERTEX_SHADER);
    const auto fragmentShaderId = _createShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    _shaderProgram = _createProgram(vertexShaderId, fragmentShaderId);

    glDeleteShader(fragmentShaderId);
    glDeleteShader(vertexShaderId);
}

//======================================================================================================================
ShaderPipeline::~ShaderPipeline()
{
    glDeleteProgram(_shaderProgram);
}

//======================================================================================================================
void ShaderPipeline::use() const
{
    glUseProgram(_shaderProgram);
}

//======================================================================================================================
void ShaderPipeline::setUniformVec3f(const String& uniformName,
                                     const float x,
                                     const float y,
                                     const float z) const
{
    const auto uniformLocation = [&] {
        auto it = _uniformLocationsByName.find(uniformName);
        if (it == _uniformLocationsByName.cend()) {
            return _uniformLocationsByName[uniformName] =
                       glGetUniformLocation(_shaderProgram, uniformName.c_str());
        }

        return it->second;
    }();

    glUniform3f(uniformLocation, x, y, z);
}

//======================================================================================================================
auto ShaderPipeline::_createShader(const String& shaderCode, const OglEnum shaderType) const -> ShaderId
{
    const auto shaderId = glCreateShader(shaderType);
    const auto shaderCodeCStr = shaderCode.c_str();
    glShaderSource(shaderId, 1, &shaderCodeCStr, nullptr);
    glCompileShader(shaderId);
    _checkShaderCompilation(shaderType, shaderId);

    return shaderId;
}

//======================================================================================================================
void ShaderPipeline::_checkShaderCompilation(const OglEnum shaderType, const ShaderId shaderId) const
{
    thread_local String msgBuffer(1024, '\0');

    const auto shaderTypeStr = [&] -> String {
        switch (shaderType) {
        case GL_VERTEX_SHADER: return "Vertex";
        case GL_FRAGMENT_SHADER: return "Fragment";
        default: return strFormat("Unknown({:#X})", shaderType);
        }
    }();

    GLint success = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success)
        return;

    glGetShaderInfoLog(shaderId, msgBuffer.size(), nullptr, &msgBuffer[0]);

    throw std::runtime_error(strFormat("Failed to compile shader of type \"{}\": {}", shaderTypeStr, msgBuffer));
}

//======================================================================================================================
auto ShaderPipeline::_createProgram(const ShaderId vertexShaderId, const ShaderId fragmentShaderId) const -> ProgramId
{
    const auto programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);
    _checkProgramLinking(programId);

    return programId;
}

//======================================================================================================================
void ShaderPipeline::_checkProgramLinking(const ProgramId programId) const
{
    thread_local String msgBuffer(1024, '\0');

    GLint success = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (success)
        return;

    glGetProgramInfoLog(programId, msgBuffer.size(), nullptr, &msgBuffer[0]);

    throw std::runtime_error(strFormat("Failed to link shader program: {}", msgBuffer));
}
