#include <OpenGlTexture/OpenGlTextureId.h>

#include <OpenGlApi/OpenGlApi.h>

#include <type_traits>

//======================================================================================================================
static_assert(std::is_same_v<opengl_texture::OpenGlTextureId, GLuint>);
