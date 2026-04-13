#pragma once

#include <Common/Integers.h>

//======================================================================================================================
namespace opengl_render_2d {
    class OglVertexArrayObject final {
    public:
        OglVertexArrayObject();

        struct BindAfterCreation final { };
        explicit OglVertexArrayObject(BindAfterCreation);

        ~OglVertexArrayObject();

        //--------------------------------------------------------------------------------------------------------------
        void use() const;

        using VaoRawId = uint32;
        VaoRawId getRawId() const;

    private:
        static void _staticAssertsOnTypedefs() noexcept;

    private:
        VaoRawId _vaoId = 0;
    };
}
