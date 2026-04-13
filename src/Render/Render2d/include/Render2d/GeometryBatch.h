#pragma once

#include <functional>

//======================================================================================================================
namespace render_2d {
    class GeometryBatchModifier;
}

//======================================================================================================================
namespace render_2d {
    class GeometryBatch {
    public:
        virtual ~GeometryBatch();

        //--------------------------------------------------------------------------------------------------------------
        virtual void modify(const std::function<void(GeometryBatchModifier&)>&) = 0;
    };
}
