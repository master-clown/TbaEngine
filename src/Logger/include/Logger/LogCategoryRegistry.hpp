#pragma once

#include <Logger/BasicLogging.h>
#include <Logger/LogCategoryRegistry.h>

#include <cassert>

//======================================================================================================================
template <class LogCategory>
void logger::LogCategoryRegistry::registerLogCategory()
{
    const auto categoryTypeIndex = std::type_index(typeid(LogCategory));
    auto [it, isInserted] = _logLevelsOfCategories.emplace(categoryTypeIndex, CategoryLevels{});
    if (!isInserted) {
        LOG_ALWAYS("Warning: trying to register an already registred LogCategory");
        return;
    }

    auto& categoryLogLevels = it->second;
    for (const auto logCategory : LogCategory{})
        categoryLogLevels.push_back(LogMessageLevel::Silent);
}

//======================================================================================================================
template <class LogCategory>
void logger::LogCategoryRegistry::setLogLevel(const LogCategory logCategory, const LogMessageLevel msgLevel)
{
    auto* categoryLevels = _getRegisteredCategoryLevels<LogCategory>();
    if (!categoryLevels) {
        LOG_ALWAYS("Warning: trying to setLogLevel({}) for an unregistered LogCategory", str(logCategory));
        return;
    }

    const auto index = _toIndexInCategoryLevels(logCategory);
    assert(index < categoryLevels->size());
    (*categoryLevels)[index] = msgLevel;
}

//======================================================================================================================
template <class LogCategory>
logger::LogMessageLevel logger::LogCategoryRegistry::getLogLevel(const LogCategory logCategory) const
{
    const auto* categoryLevels = _getRegisteredCategoryLevels<LogCategory>();
    if (!categoryLevels)
        return LogMessageLevel::Silent;

    const auto index = _toIndexInCategoryLevels(logCategory);
    assert(index < categoryLevels->size());
    return (*categoryLevels)[index];
}

//======================================================================================================================
template <class LogCategory>
size_t logger::LogCategoryRegistry::_toIndexInCategoryLevels(const LogCategory logCategory)
{
    return static_cast<size_t>(logCategory);
}

//======================================================================================================================
template <class LogCategory>
auto logger::LogCategoryRegistry::_getRegisteredCategoryLevels() -> CategoryLevels*
{
    return const_cast<CategoryLevels*>(
        static_cast<const LogCategoryRegistry&>(*this)._getRegisteredCategoryLevels<LogCategory>());
}

//======================================================================================================================
template <class LogCategory>
auto logger::LogCategoryRegistry::_getRegisteredCategoryLevels() const -> const CategoryLevels*
{
    const auto categoryTypeIndex = std::type_index(typeid(LogCategory));
    auto it = _logLevelsOfCategories.find(categoryTypeIndex);
    if (it == _logLevelsOfCategories.cend())
        return nullptr;

    return &it->second;
}
