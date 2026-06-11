#include <OpenGlTexture/OpenGlTextureHandle.h>

#include <OpenGlApi/OpenGlApi.h>

#include <type_traits>

//======================================================================================================================
static_assert(std::is_same_v<opengl_texture::OpenGlTextureHandle, GLuint64>);
