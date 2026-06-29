#pragma once

#include <Common/String.h>

//======================================================================================================================
namespace opengl_api {
    void checkOperationSuccess(const String& operationDescription);
    void logOnOperationFailure(const String& operationDescription) noexcept;
}
