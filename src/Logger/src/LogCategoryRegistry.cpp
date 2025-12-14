#include <Logger/LogCategoryRegistry.hpp>

//======================================================================================================================
auto logger::LogCategoryRegistry::getInstance() -> LogCategoryRegistry&
{
    static LogCategoryRegistry logCategoryRegistry;
    return logCategoryRegistry;
}

//======================================================================================================================
logger::LogCategoryRegistry::LogCategoryRegistry() = default;
