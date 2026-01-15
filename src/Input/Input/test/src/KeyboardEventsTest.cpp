#include <GuiAppTemplate/GuiAppTemplate.h>

#include <AppEvent/AppEvent.hpp>
#include <Logger/BasicLogging.h>
#include <SdlFramework/SdlFramework.h>

#include <gtest/gtest.h>

//======================================================================================================================
#define TEST_SUITE_NAME KeyboardEventsTest
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//======================================================================================================================
class BaseKeyboardEventsTestApp : public gui_app_template::GuiAppTemplate {
    using Super = gui_app_template::GuiAppTemplate;

public:
    explicit BaseKeyboardEventsTestApp()
        : Super(winsys::WindowOptions{
              .wndTitle = STRINGIFY(TEST_SUITE_NAME) + String(" - type any keys and see key events in stdout"),
          })
    {
    }

protected:
    ShouldQuit _processEvent(const app_event::AppEvent& appEvent) override
    {
        if (Super::_processEvent(appEvent) == ShouldQuit{true})
            return ShouldQuit{true};

        if (const auto* keyEvent = appEvent.getIf<input_event::KeyboardEvent>()) {
            LOG_ALWAYS(str(*keyEvent));
        }

        return ShouldQuit{false};
    }
};

//======================================================================================================================
#define TEST_CASE(name) TEST(TEST_SUITE_NAME, name)

//======================================================================================================================
TEST_CASE(SdlKeyboard)
{
    class SdlApp final : public BaseKeyboardEventsTestApp {
    private:
        uptr<framework::Framework> _createFramework() override
        {
            return makeUPtr<sdl_framework::SdlFramework>();
        }
    };

    SdlApp app;
    EXPECT_NO_THROW(app.run());
}
