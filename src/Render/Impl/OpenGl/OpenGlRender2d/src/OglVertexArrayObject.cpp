#include "OglVertexArrayObject.h"

#include <OpenGlApi/OpenGlApi.h>

#include <type_traits>

//======================================================================================================================
using opengl_render_2d::OglVertexArrayObject;

//======================================================================================================================
void OglVertexArrayObject::_staticAssertsOnTypedefs() noexcept
{
    static_assert(std::is_same_v<VaoRawId, GLuint>);
}

//======================================================================================================================
OglVertexArrayObject::OglVertexArrayObject()
{
    glGenVertexArrays(1, &_vaoId);
}

//======================================================================================================================
OglVertexArrayObject::OglVertexArrayObject(BindAfterCreation)
    : OglVertexArrayObject()
{
    use();
}

//======================================================================================================================
OglVertexArrayObject::~OglVertexArrayObject()
{
    glDeleteVertexArrays(1, &_vaoId);
}

//======================================================================================================================
void OglVertexArrayObject::use() const
{
    glBindVertexArray(_vaoId);
}

//======================================================================================================================
auto OglVertexArrayObject::getRawId() const -> VaoRawId
{
    return _vaoId;
}
