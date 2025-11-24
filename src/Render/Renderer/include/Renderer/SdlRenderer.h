#pragma once

#include <Renderer/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace render_2d {
    class Renderer;
}

//======================================================================================================================
namespace render {
    //==================================================================================================================
    class SdlRenderer final : public Renderer {
    public:
        SdlRenderer();
        ~SdlRenderer();

        render_2d::Renderer& get2dRenderer() override;
        render_3d::Renderer& get3dRenderer() override;

    private:
        uptr<render_2d::Renderer> _renderer2d;
    };
}
