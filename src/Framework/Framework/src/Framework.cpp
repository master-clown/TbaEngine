#include <Framework/Framework.h>

#include <Renderer/Renderer.h>
#include <Winsys/WindowMgr.h>
#include <Winsys/WindowOptions.h>

#ifdef ENABLE_LOG
#include <Input/LogCategory.h>
#include <Logger/LogCategoryRegistry.hpp>
#endif

//======================================================================================================================
using namespace framework;

//======================================================================================================================
Framework::Framework()
{
    Framework::enableStaticLogCategories();
}

//======================================================================================================================
Framework::~Framework() = default;

//======================================================================================================================
auto Framework::createWindowWithRenderer(winsys::WindowOptions winOpts,
                                         const renderer_info::RendererType renderType)
    -> WindowWithRenderer
{
    winOpts.initForRendererOfType = renderType;

    auto window = getWindowMgr().createWindow(std::move(winOpts));
    auto renderer = createRenderer(renderType, *window);

    return {.window = std::move(window), .renderer = std::move(renderer)};
}

//======================================================================================================================
void Framework::enableStaticLogCategories()
{
#ifdef ENABLE_LOG
    static bool isAlreadyEnabled = false;

    if (isAlreadyEnabled)
        return;

    auto& logCategoryRegistry = logger::LogCategoryRegistry::getInstance();

    //// LogCategory registrations
    logCategoryRegistry.registerLogCategory<input::LogCategory>();

    //// setLogLevel calls
    // logCategoryRegistry.setLogLevel(input::LogCategory::KeyboardEvents, logger::LogMessageLevel::Trace);

    isAlreadyEnabled = true;
#endif
}
