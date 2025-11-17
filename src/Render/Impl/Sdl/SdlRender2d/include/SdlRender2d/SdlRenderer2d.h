#pragma once

#include <Render2d/Renderer.h>

//======================================================================================================================
namespace sdl_render {
    //==================================================================================================================
    class SdlRenderer2d final : public render_2d::Renderer {
    public:
        SdlRenderer2d();
        ~SdlRenderer2d();
    };
}
