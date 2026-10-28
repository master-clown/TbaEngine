#pragma once

#include <RenderScene/Renderable2d.h>

//======================================================================================================================
namespace render_scene {
    class Renderable final {
    public:
        explicit Renderable(Renderable2d);
        Renderable();

        const Renderable2d& getRenderable2d() const noexcept;

    private:
        Renderable2d _2dPart;
    };
}
