#include <GuiAppTemplate/GuiAppTemplate.h>

#include <SdlFramework/SdlFramework.h>
#include <SdlRenderContext/SdlRenderPreconfigOptions.h>
#include <Winsys/WindowMgr.h>

#include <gtest/gtest.h>

//======================================================================================================================
#define TEST_SUITE_NAME SdlRendererCreationTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//======================================================================================================================
class BaseSdlRenderTestApp : public gui_app_template::GuiAppTemplate {
    using Super = gui_app_template::GuiAppTemplate;

public:
    explicit BaseSdlRenderTestApp(const String& caseDescription)
        : Super(winsys::WindowOptions{
              .wndTitle = STRINGIFY(TEST_SUITE_NAME) + String(" - ") + caseDescription,
          })
    {
    }

protected:
    uptr<winsys::Window> _createWindow(const winsys::WindowOptions& windowOptions) override
    {
        return getFramework().getWindowMgr().createWindow({
            .winOptions = windowOptions,
            .rendererPreconfigOptions = makeUPtr<sdl_render_context::SdlRenderPreconfigOptions>(),
        });
    }

    uptr<framework::Framework> _createFramework() override
    {
        return makeUPtr<sdl_framework::SdlFramework>();
    }
};

//======================================================================================================================
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//======================================================================================================================
TEST_CASE(CreateEmptyScreen)
{
    BaseSdlRenderTestApp app("Just run and finish without any exceptions");
    EXPECT_NO_THROW(app.run());
}
