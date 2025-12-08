#pragma once

#include <Logger/LogCategoryRegistry.h>

#include <cassert>
#include <stdexcept>

//======================================================================================================================
template <class LogCategory>
void logger::LogCategoryRegistry::registerLogCategory()
{
    const auto categoryTypeIndex = std::type_index(typeid(LogCategory));
    auto& categoryLogLevels = [&]() -> CategoryLevels& {
        auto [it, alreadyExists] = _logLevelsOfCategories.emplace(categoryTypeIndex);
        assert(!alreadyExists && "Trying to register same category twice");

        return it->second;
    }();

    for (const auto logCategory : LogCategory{})
        categoryLogLevels[static_cast<std::underlying_type_t<LogCategory>>(logCategory)] = LogMessageLevel::Silent;
}

//======================================================================================================================
template <class LogCategory>
void logger::LogCategoryRegistry::setLogLevel(const LogCategory logCategory, const LogMessageLevel msgLevel)
{
    _getRegisteredCategoryLevels<LogCategory>()[_toIndexInCategoryLevels(logCategory)] = msgLevel;
}

//======================================================================================================================
template <class LogCategory>
logger::LogMessageLevel logger::LogCategoryRegistry::getLogLevel(const LogCategory logCategory) const
{
    return _getRegisteredCategoryLevels<LogCategory>()[_toIndexInCategoryLevels(logCategory)];
}

//======================================================================================================================
template <class LogCategory>
size_t logger::LogCategoryRegistry::_toIndexInCategoryLevels(const LogCategory logCategory)
{
    return static_cast<size_t>(logCategory);
}

//======================================================================================================================
template <class LogCategory>
auto logger::LogCategoryRegistry::_getRegisteredCategoryLevels() -> CategoryLevels&
{
    const auto categoryTypeIndex = std::type_index(typeid(LogCategory));
    auto it = _logLevelsOfCategories.find(categoryTypeIndex);
    if (it == _logLevelsOfCategories.cend())
        throw std::runtime_error("Trying to get CategoryLevels for an unregistered log category");

    return it->second;
}
