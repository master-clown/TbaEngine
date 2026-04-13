#pragma once

#include <Common/Integers.h>
#include <Common/Stl/HashMap.h>
#include <Common/String.h>

//======================================================================================================================
namespace opengl_render_2d {
    class ShaderPipeline final {
    public:
        ShaderPipeline(const String& vertexShaderCode, const String& fragmentShaderCode);
        ~ShaderPipeline();

        void use() const;

        void setUniformVec3f(const String& uniformName,
                             const float x,
                             const float y,
                             const float z) const;

    private:
        using OglEnum = uint32;
        using ShaderId = uint32;
        using ProgramId = uint32;

        ShaderId _createShader(const String& shaderCode, OglEnum shaderType) const;
        void _checkShaderCompilation(OglEnum shaderType, ShaderId) const;
        ProgramId _createProgram(ShaderId vertexShaderId, ShaderId fragmentShaderId) const;
        void _checkProgramLinking(ProgramId) const;

        //--------------------------------------------------------------------------------------------------------------
        static void _staticAssertsOnTypedefs() noexcept;

    private:
        using UniformLocation = int;

        ProgramId _shaderProgram;
        mutable HashMap<String, UniformLocation> _uniformLocationsByName;
    };
}
