#pragma once

#include <Logger/LogMessageLevel.h>

#include <typeindex>
#include <unordered_map>
#include <vector>

//======================================================================================================================
namespace logger {
    //==================================================================================================================
    class LogCategoryRegistry final {
    public:
        //--------------------------------------------------------------------------------------------------------------
        template <class LogCategory>
        void registerLogCategory();

        //--------------------------------------------------------------------------------------------------------------
        template <class LogCategory>
        void setLogLevel(LogCategory, LogMessageLevel);

        template <class LogCategory>
        LogMessageLevel getLogLevel(LogCategory) const;

        //--------------------------------------------------------------------------------------------------------------
        LogCategoryRegistry& getInstance();

    private:
        using CategoryLevels = std::vector<LogMessageLevel>;
        using CategoryTypeIndex = std::type_index;

    private:
        LogCategoryRegistry();
        LogCategoryRegistry(const LogCategoryRegistry&) = delete;

        //--------------------------------------------------------------------------------------------------------------
        template <class LogCategory>
        static size_t _toIndexInCategoryLevels(LogCategory);

        template <class LogCategory>
        CategoryLevels& _getRegisteredCategoryLevels();

    private:
        std::unordered_map<CategoryTypeIndex, CategoryLevels> _logLevelsOfCategories;
    };
}
