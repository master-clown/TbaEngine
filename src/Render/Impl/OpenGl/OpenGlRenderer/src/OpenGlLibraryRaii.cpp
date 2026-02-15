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
}

//==================================================================================================================
OpenGlLibraryRaii::~OpenGlLibraryRaii() = default;
