#include <OpenGlApi/ErrorCheck.h>

#include <OpenGlApi/OpenGlApi.h>

#include <Logger/BasicLogging.h>

#include <stdexcept>

//======================================================================================================================
void opengl_api::checkOperationSuccess(const String& operationDescription)
{
    if (const auto lastGlError = glGetError(); lastGlError != GL_NO_ERROR)
        throw std::runtime_error(strFormat("OpenGL operation failed\nDescription: {}\nOGL Error code: {}",
                                           operationDescription,
                                           lastGlError));
}

//======================================================================================================================
void opengl_api::logOnOperationFailure(const String& operationDescription) noexcept
{
    if (const auto lastGlError = glGetError(); lastGlError != GL_NO_ERROR)
        LOG_ERROR("OpenGL operation failed\nDescription: {}\nOGL Error code: {}",
                  operationDescription,
                  lastGlError);
}
