#pragma once

#include <GuiAppTemplate/GuiAppWithRenderer.h>

#include <Framework/Framework.h>
#include <Render2d/Renderer.h>
#include <Renderer/Renderer.h>
#include <Winsys/Window.h>
#include <Winsys/WindowMgr.h>

//======================================================================================================================
template <class RendererPreconfigOptions>
gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions>::GuiAppWithRenderer(winsys::WindowOptions winOptions)
    : Super(std::move(winOptions))
{
}

//======================================================================================================================
template <class RendererPreconfigOptions>
void gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions>::_init()
{
    Super::_init();

    _initAppWithRenderer();
}

//======================================================================================================================
template <class RendererPreconfigOptions>
uptr<winsys::Window> gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions>::_createWindow(
    const winsys::WindowOptions& winOptions)
{
    auto window = getFramework().getWindowMgr().createWindow({
        .winOptions = winOptions,
        .rendererPreconfigOptions = makeUPtr<RendererPreconfigOptions>(),
    });

    _renderer = getFramework().createRenderer(window->createRendererContext());
    _renderer->get2dRenderer().setBaseRenderResolution(winOptions.wndWidth, winOptions.wndHeight);

    return window;
}

//======================================================================================================================
template <class RendererPreconfigOptions>
render::Renderer& gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions>::getRenderer()
{
    return *_renderer;
}
