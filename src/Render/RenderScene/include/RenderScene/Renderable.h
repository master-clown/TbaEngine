#pragma once

#include <RenderScene/Renderable2d.h>

//======================================================================================================================
namespace render_scene {
    class Renderable {
    public:
        explicit Renderable(Renderable2d renderable2d)
            : _2dPart(std::move(renderable2d))
        {
        }

        virtual ~Renderable() = default;

    protected:
        Renderable2d _2dPart;
    };
}
