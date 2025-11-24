#include "GuiTest.h"

#include <AppEvent/EventInfo.hpp>
#include <Common/Memory.h>
#include <Framework/SdlFramework.h>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <Render2d/Renderer.h>
#include <Renderer/Renderer.h>
#include <Winsys/WindowMgr.h>

//======================================================================================================================
GuiTest::GuiTest() = default;

//----------------------------------------------------------------------------------------------------------------------
GuiTest::~GuiTest() = default;

//======================================================================================================================
uptr<framework::Framework> GuiTest::_init()
{
    auto fr = makeUPtr<framework::SdlFramework>();

    _initWindow(*fr);
    _initRenderer(*fr);

    return fr;
}

//======================================================================================================================
auto GuiTest::_iterate(const app_event::AppEvent& appEventVariant) -> ShouldQuit
{
    const auto shouldQuit = _processEvent(appEventVariant);

    _render();

    return shouldQuit;
}

//======================================================================================================================
void GuiTest::_initWindow(framework::Framework& fr)
{
    _appWindow = fr.getWindowMgr().createWindow(winsys::WindowOptions{
        .wndTitle = "Hello!",
        .wndWidth = _graphicsOptions._renderTargetLogicalWidth,
        .wndHeight = _graphicsOptions._renderTargetLogicalHeigth,
    });
}

//======================================================================================================================
void GuiTest::_initRenderer(framework::Framework& fr)
{
    _renderer = fr.createRenderer(render::RendererType::Sdl, *_appWindow);
    _renderer->get2dRenderer().setBaseRenderResolution(_graphicsOptions._renderTargetLogicalWidth,
                                                       _graphicsOptions._renderTargetLogicalHeigth);
}

//======================================================================================================================
auto GuiTest::_processEvent(const app_event::AppEvent& appEventVariant) -> ShouldQuit
{
    if (const auto* windowEvent = std::get_if<app_event::WindowEvent>(&appEventVariant)) {
        using Kind = app_event::WindowEventKind;
        switch (windowEvent->getKind()) {
        case Kind::QuitRequested: return ShouldQuit{true};
        }
    }

    return ShouldQuit{false};
}

//======================================================================================================================
void GuiTest::_render()
{
    _renderer->clear(content::Color::black);

    auto& renderer2d = _renderer->get2dRenderer();

    const auto point = render_2d::RenderableGeometry<geometry_2d::Point2d>{
        .primitive = geometry_2d::Point2d{.x = 400, .y = 200},
        .contentTraits = geometry_2d::ContentTraits<geometry_2d::Point2d>{
            .color = content::Color{.r = 128},
        },
    };

    const auto line = render_2d::RenderableGeometry<geometry_2d::Line>{
        .primitive = geometry_2d::Line{.startPt = {.x = 100, .y = 100},
                                       .finalPt = {.x = 400, .y = 400}},
    };

    const auto triangle = render_2d::RenderableGeometry<geometry_2d::Triangle>{
        .primitive = geometry_2d::Triangle{
            .pt1 = {.x = 500, .y = 300},
            .pt2 = {.x = 625, .y = 400},
            .pt3 = {.x = 450, .y = 380},
        },
        .contentTraits = geometry_2d::ContentTraits<geometry_2d::Triangle>{
            .faceContent = content::Color{.b = 200},
        },
    };

    renderer2d.render(point);
    renderer2d.render(line);
    renderer2d.render(triangle);

    _renderer->finalizeRender();
}
