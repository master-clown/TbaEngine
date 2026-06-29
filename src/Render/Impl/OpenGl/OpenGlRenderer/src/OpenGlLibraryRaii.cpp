#include "OpenGlLibraryRaii.h"

#include <Glad/glad/glad.h>

#include <cassert>
#include <stdexcept>

//==================================================================================================================
using namespace opengl_renderer;

//==================================================================================================================
OpenGlLibraryRaii::OpenGlLibraryRaii(const LibraryInitOptions& initOptions)
{
    assert(initOptions.openGlFunctionsLoader &&
           "OpenGL function loader is required to use OpenGL (frameworks like SDL and GLFW provide them)");

    if (!gladLoadGLLoader(initOptions.openGlFunctionsLoader))
        throw std::runtime_error("Failed to initialize OpenGL library with gladLoadGLLoader()");

    _checkRequiredExtensions();
}

//==================================================================================================================
OpenGlLibraryRaii::~OpenGlLibraryRaii() = default;

//==================================================================================================================
void OpenGlLibraryRaii::_checkRequiredExtensions() const
{
#ifdef OPENGL_USE_BINDLESS_TEXTURES
    if (!GLAD_GL_ARB_bindless_texture)
        throw std::runtime_error("Extension GL_ARB_bindless_texture is not supported");
#endif
}
