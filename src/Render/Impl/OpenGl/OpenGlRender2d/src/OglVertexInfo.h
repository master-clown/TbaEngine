#pragma once

#include <Render2d/VertexInfo.h>

//======================================================================================================================
namespace opengl_render_2d {
    struct OglVertexInfo final {
        render_2d::VertexInfo baseVertexInfo;

        // TODO: change this ad-hoc when the `libContent` is properly designed
        uint32 textureHandleLower4Bytes = 0;
        uint32 textureHandleUpper4Bytes = 0;
    };
}
