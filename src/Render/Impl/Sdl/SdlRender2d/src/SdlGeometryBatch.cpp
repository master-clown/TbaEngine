#include "SdlGeometryBatch.h"

#include "SdlGeometryBatchModifier.h"

#include "Details/PrimitiveVariant.h"

#include <cassert>

//======================================================================================================================
using sdl_render_2d::SdlGeometryBatch;
using sdl_render_2d::details::PrimitiveVariant;

//======================================================================================================================
SdlGeometryBatch::SdlGeometryBatch()
    : _modifier(makeUPtr<SdlGeometryBatchModifier>(*this))
{
}

//======================================================================================================================
SdlGeometryBatch::~SdlGeometryBatch() = default;

//======================================================================================================================
void SdlGeometryBatch::modify(const std::function<void(render_2d::GeometryBatchModifier&)>& modify)
{
    assert(_modifier);
    modify(*_modifier);
}

//======================================================================================================================
auto SdlGeometryBatch::_getPrimitives() const -> const Vector<PrimitiveVariant>&
{
    return _primitives;
}

//======================================================================================================================
auto SdlGeometryBatch::_getPrimitives() -> Vector<PrimitiveVariant>&
{
    return _primitives;
}
