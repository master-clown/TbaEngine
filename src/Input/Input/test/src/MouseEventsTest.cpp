#include <GuiAppTemplate/GuiAppTemplate.h>

#include <AppEvent/AppEvent.hpp>
#include <Logger/BasicLogging.h>
#include <SdlFramework/SdlFramework.h>

#include <gtest/gtest.h>

//======================================================================================================================
#define TEST_SUITE_NAME MouseEventsTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//======================================================================================================================
class BaseMouseEventsTestApp : public gui_app_template::GuiAppTemplate {
    using Super = gui_app_template::GuiAppTemplate;

public:
    explicit BaseMouseEventsTestApp()
        : Super(winsys::WindowOptions{
              .wndTitle = STRINGIFY(TEST_SUITE_NAME) + String(" - use mouse and see mouse events in stdout"),
          })
    {
    }

protected:
    ShouldQuit _processEvent(const app_event::AppEvent& appEvent) override
    {
        if (Super::_processEvent(appEvent) == ShouldQuit{true})
            return ShouldQuit{true};

        if (const auto* mouseEvent = appEvent.getIf<input_event::MouseEvent>()) {
            LOG_ALWAYS(str(*mouseEvent));
        }

        return ShouldQuit{false};
    }
};

//======================================================================================================================
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//======================================================================================================================
TEST_CASE(SdlMouse)
{
    class SdlApp final : public BaseMouseEventsTestApp {
    private:
        uptr<framework::Framework> _createFramework() override
        {
            return makeUPtr<sdl_framework::SdlFramework>();
        }
    };

    SdlApp app;
    EXPECT_NO_THROW(app.run());
}
