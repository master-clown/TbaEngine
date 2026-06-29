#pragma once

#include "OglVertexInfo.h"
#include "TypedOglBuffer.h"

#include <string_view>

//======================================================================================================================
namespace opengl_render_2d {
    class OglVertexBuffer final {
    public:
        using VaoId = uint32;

        // TODO: use `const VertexArrayObject&` instead of `VaoId`
        explicit OglVertexBuffer(VaoId);

        using VboRawId = OglBuffer::BufferRawId;
        VboRawId getVboId() const;

        TypedOglBuffer<OglVertexInfo>& getUnderlyingBuffer();

        //--------------------------------------------------------------------------------------------------------------
        static const std::string_view& getVertexShaderText();
        static const std::string_view& getFragmentShaderText();

    private:
        void _rebindVboToVao() const;

        //--------------------------------------------------------------------------------------------------------------
        static void _staticAssertsOnTypedefs() noexcept;

    private:
        VaoId _vaoId;
        TypedOglBuffer<OglVertexInfo> _buffer;
    };
}
