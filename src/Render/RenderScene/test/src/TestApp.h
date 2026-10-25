#pragma once

#include <GuiAppTemplate/GuiAppWithRenderer.hpp>
#include <Input/KeyboardState.h>
#include <OpenGlContext/OpenGlPreconfigOptions.h>
#include <RenderScene/RenderScene.h>

#include <functional>

//======================================================================================================================
class TestApp final
    : public gui_app_template::GuiAppWithRenderer<opengl_context::OpenGlPreconfigOptions> {
    using Super = gui_app_template::GuiAppWithRenderer<opengl_context::OpenGlPreconfigOptions>;

public:
    explicit TestApp(const String& wndTitle);

    render_scene::RenderScene& getRenderScene();
    const input::KeyboardState& getKeyboardState(); // TODO: mark as const

    using OnIterate = std::function<void(const app_event::AppEvent&)>;
    void onIterate(OnIterate);

private:
    void _initAppWithRenderer() override;
    ShouldQuit _iterate(const app_event::AppEvent&) override;
    void _render() override;
    uptr<framework::Framework> _createFramework() override;

    //------------------------------------------------------------------------------------------------------------------
    uptr<render_scene::RenderScene> _renderScene;
    OnIterate _onIterate;
};
