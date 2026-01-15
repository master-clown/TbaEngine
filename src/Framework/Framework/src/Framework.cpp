#include <Framework/Framework.h>

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
