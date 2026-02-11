#include <OpenGlContext/OpenGlContext.h>

#include "OpenGlLibraryRaii.h"

//======================================================================================================================
using opengl_context::OpenGlContext;
using opengl_context::OpenGlLibraryRaii;

//======================================================================================================================
OpenGlContext::OpenGlContext(LoadOpenGlFunction loadOpenGlFunction)
    : _openGlLibraryRaii(makeUPtr<OpenGlLibraryRaii>(OpenGlLibraryRaii::LibraryInitOptions{
          .loadOpenGlFunction = loadOpenGlFunction,
      }))
{
}

//======================================================================================================================
OpenGlContext::~OpenGlContext() = default;

//======================================================================================================================
renderer_context::RendererType OpenGlContext::getRendererType() const
{
    return renderer_context::RendererType::OpenGl;
}
