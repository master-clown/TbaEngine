#include <GuiAppTemplate/GuiAppTemplate.h>

#include <OpenGlContext/OpenGlPreconfigOptions.h>
#include <SdlFramework/SdlFramework.h>
#include <Winsys/WindowMgr.h>

#include <gtest/gtest.h>

//======================================================================================================================
#define TEST_SUITE_NAME OpenGlRendererCreationOnSdlTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//======================================================================================================================
class BaseOpenGlOnSdlTestApp : public gui_app_template::GuiAppTemplate {
    using Super = gui_app_template::GuiAppTemplate;

public:
    explicit BaseOpenGlOnSdlTestApp(const String& caseDescription)
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
            .rendererPreconfigOptions = makeUPtr<opengl_context::OpenGlPreconfigOptions>(),
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
    BaseOpenGlOnSdlTestApp app("Just run and finish without any exceptions");
    EXPECT_NO_THROW(app.run());
}
