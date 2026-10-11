#include "TestApp.h"

#include <Content/Color.h>
#include <SdlFramework/SdlFramework.h>
#include <Winsys/WindowOptions.h>

//======================================================================================================================
TestApp::TestApp(const String& wndTitle)
    : Super(winsys::WindowOptions{
          .wndTitle = wndTitle,
      })
{
}

//======================================================================================================================
render_scene::RenderScene& TestApp::getRenderScene()
{
    return *_renderScene;
}

//======================================================================================================================
void TestApp::onIterate(OnIterate onIterate)
{
    _onIterate = std::move(onIterate);
}

//======================================================================================================================
void TestApp::_initAppWithRenderer()
{
    auto& renderer = this->getRenderer();

    auto& renderer2d = renderer.get2dRenderer();
    _renderScene = std::make_unique<render_scene::RenderScene>(renderer2d);
}

//======================================================================================================================
auto TestApp::_iterate(const app_event::AppEvent& appEvent) -> ShouldQuit
{
    if (_onIterate)
        _onIterate(appEvent);

    return Super::_iterate(appEvent);
}

//======================================================================================================================
void TestApp::_render()
{
    this->getRenderer().clear(content::Color::black);

    auto& renderer2d = this->getRenderer().get2dRenderer();
    renderer2d.renderGeometryBatch(getRenderScene().getGeometryBatch2d());

    this->getRenderer().finalizeRender();
}

//======================================================================================================================
uptr<framework::Framework> TestApp::_createFramework()
{
    return makeUPtr<sdl_framework::SdlFramework>();
}
