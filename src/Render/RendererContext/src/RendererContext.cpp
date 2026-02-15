#include <RendererContext/RendererContext.h>

//======================================================================================================================
using renderer_context::RendererContext;

//======================================================================================================================
RendererContext::~RendererContext() = default;

//======================================================================================================================
void RendererContext::initContext(TargetWindow& targetWindow)
{
    _targetWindow = &targetWindow;

    _initContext();
}

//======================================================================================================================
void RendererContext::freeContext()
{
    _freeContext();

    _targetWindow = nullptr;
}

//======================================================================================================================
auto RendererContext::getTargetWindow() const -> TargetWindow*
{
    return _targetWindow;
}
