#include "GuiTest.h"

#include <AppEvent/AppEvent.h>
#include <Common/Memory.h>
#include <EventInfo/EventInfo.hpp>
#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <OpenGlContext/OpenGlPreconfigOptions.h>
#include <Render2d/GeometryBatch.h>
#include <Render2d/GeometryBatchModifier.h>
#include <Render2d/Renderer.h>
#include <Renderer/Renderer.h>
#include <SdlFramework/SdlFramework.h>
#include <SdlRenderContext/SdlRenderPreconfigOptions.h>
#include <Winsys/WindowMgr.h>

//======================================================================================================================
GuiTest::GuiTest()
    : framework::RenderableApplication(framework::RefreshRateOptions{})
{
}

//----------------------------------------------------------------------------------------------------------------------
GuiTest::~GuiTest() = default;

//======================================================================================================================
uptr<framework::Framework> GuiTest::_createFramework()
{
    return makeUPtr<sdl_framework::SdlFramework>();
}

//======================================================================================================================
void GuiTest::_init()
{
    _initWindow(getFramework());
    _initRenderer(getFramework());

    auto& renderer2d = _renderer->get2dRenderer();

    _simple2dGeometryBatch = renderer2d.createGeometryBatch();
    _simple2dGeometryBatch->modify([&](render_2d::GeometryBatchModifier& modifier) {
        const auto point = render_2d::RenderableGeometry<geometry_2d::Point2d>{
            .primitive = geometry_2d::Point2d{.x = -0.9, .y = 0.9},
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Point2d>{
                .color = content::Color{.b = 255},
            },
        };

        const auto line = render_2d::RenderableGeometry<geometry_2d::Line>{
            .primitive = geometry_2d::Line{.startPt = {.x = 0.0, .y = 0.8},
                                           .finalPt = {.x = -0.5, .y = -0.4}},
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Line>{
                .lineColor = {.r = 100},
            },
        };

        const auto triangle = render_2d::RenderableGeometry<geometry_2d::Triangle>{
            .primitive = geometry_2d::Triangle{
                .pt1 = {.x = 0.5, .y = -0.2},
                .pt2 = {.x = 0.8, .y = -0.6},
                .pt3 = {.x = 0.3, .y = -0.5},
            },
            .contentTraits = geometry_2d::ContentTraits<geometry_2d::Triangle>{
                .faceContent = content::Color{.g = 255},
            },
        };

        modifier.add(point);
        modifier.add(line);
        modifier.add(triangle);
    });
}

//======================================================================================================================
auto GuiTest::_iterate(const app_event::AppEvent& appEventVariant) -> ShouldQuit
{
    const auto shouldQuit = _processEvent(appEventVariant);

    return shouldQuit;
}

//======================================================================================================================
void GuiTest::_render()
{
    _renderer->clear(content::Color::black);

    _renderer->get2dRenderer().renderGeometryBatch(*_simple2dGeometryBatch);

    _renderer->finalizeRender();
}

//======================================================================================================================
void GuiTest::_initWindow(framework::Framework& fr)
{
    _appWindow = fr.getWindowMgr().createWindow({
        .winOptions = winsys::WindowOptions{
            .wndTitle = "Hello!",
            .wndWidth = _graphicsOptions._renderTargetLogicalWidth,
            .wndHeight = _graphicsOptions._renderTargetLogicalHeigth,
        },
        .rendererPreconfigOptions = makeUPtr<sdl_render_context::SdlRenderPreconfigOptions>(),
    });
}

//======================================================================================================================
void GuiTest::_initRenderer(framework::Framework& fr)
{
    _renderer = fr.createRenderer(_appWindow->createRendererContext());
    _renderer->get2dRenderer().setBaseRenderResolution(_graphicsOptions._renderTargetLogicalWidth,
                                                       _graphicsOptions._renderTargetLogicalHeigth);
}

//======================================================================================================================
auto GuiTest::_processEvent(const app_event::AppEvent& appEvent) -> ShouldQuit
{
    if (const auto* windowEvent = std::get_if<win_event::WindowEvent>(&appEvent.getVariant())) {
        using Kind = win_event::WindowEventKind;
        switch (windowEvent->getKind()) {
        case Kind::QuitRequested: return ShouldQuit{true};
        }
    }

    return ShouldQuit{false};
}
