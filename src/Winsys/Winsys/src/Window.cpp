#include <Winsys/Window.h>

#include <RendererContext/RendererContextCreator.h>
#include <RendererContext/RendererContextRaii.h>

#include <stdexcept>

//======================================================================================================================
using namespace winsys;

//======================================================================================================================
Window::Window(WindowOptions options, uptr<renderer_context::RendererContextCreator> rendererContextCreator)
    : _windowOptions(std::move(options))
    , _rendererContextCreator(std::move(rendererContextCreator))
{
    if (_rendererContextCreator)
        _rendererContextCreator->configureBeforeWindowCreation();
}

//----------------------------------------------------------------------------------------------------------------------
Window::~Window() = default;

//======================================================================================================================
renderer_context::RendererContextRaii Window::createRendererContext()
{
    if (!_rendererContextCreator)
        throw std::runtime_error("Cannot create RendererContext since a RendererContextCreator was not specified");

    return _rendererContextCreator->createRendererContext(*this);
}

//======================================================================================================================
const WindowOptions& Window::getWindowOptions() const
{
    return _windowOptions;
}

//======================================================================================================================
Optional<renderer_context::RendererType> Window::_getBindedRendererType() const
{
    if (_rendererContextCreator)
        return _rendererContextCreator->getRendererType();

    return {};
}
