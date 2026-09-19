#pragma once

#include <RenderScene/Renderable2d.h>

//======================================================================================================================
namespace render_scene {
    // To access particular parts of the `Renderable` it is best to provide accessors in
    // the corresponding `RenderableBlueprint` and use them here. No common interfaces are
    // defined for now, when it is not obvious how they must look like.
    class Renderable final {
    public:
        explicit Renderable(Renderable2d);
        Renderable();

        const Renderable2d& getRenderable2d() const noexcept;

    private:
        Renderable2d _2dPart;
    };
}
