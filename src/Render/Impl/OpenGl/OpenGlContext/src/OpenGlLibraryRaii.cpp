#include "OpenGlLibraryRaii.h"

#include <Glad/glad/glad.h>

#include <cassert>

//==================================================================================================================
using namespace opengl_context;

//==================================================================================================================
OpenGlLibraryRaii::OpenGlLibraryRaii(const LibraryInitOptions& initOptions)
{
    assert(initOptions.loadOpenGlFunction &&
           "OpenGL function loader is required to use OpenGL (frameworks like SDL and GLFW provide them)");

    gladLoadGLLoader(initOptions.loadOpenGlFunction);
}

//==================================================================================================================
OpenGlLibraryRaii::~OpenGlLibraryRaii() = default;
