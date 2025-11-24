#pragma once

#include <Render2d/Renderer.h>

//======================================================================================================================
namespace render_2d {
    //==================================================================================================================
    class SdlRenderer final : public Renderer {
    public:
        SdlRenderer();
        ~SdlRenderer();
    };
}
