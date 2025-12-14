#pragma once

#include <Logger/LogCategoryConcept.h>
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
        template <LogCategoryConcept LogCategory>
        void registerLogCategory();

        //--------------------------------------------------------------------------------------------------------------
        template <LogCategoryConcept LogCategory>
        void setLogLevel(LogCategory, LogMessageLevel);

        template <LogCategoryConcept LogCategory>
        LogMessageLevel getLogLevel(LogCategory) const;

        //--------------------------------------------------------------------------------------------------------------
        static LogCategoryRegistry& getInstance();

    private:
        using CategoryLevels = std::vector<LogMessageLevel>;
        using CategoryTypeIndex = std::type_index;

    private:
        LogCategoryRegistry();
        LogCategoryRegistry(const LogCategoryRegistry&) = delete;

        //--------------------------------------------------------------------------------------------------------------
        template <LogCategoryConcept LogCategory>
        static size_t _toIndexInCategoryLevels(LogCategory);

        template <LogCategoryConcept LogCategory>
        CategoryLevels* _getRegisteredCategoryLevels();

        template <LogCategoryConcept LogCategory>
        const CategoryLevels* _getRegisteredCategoryLevels() const;

    private:
        std::unordered_map<CategoryTypeIndex, CategoryLevels> _logLevelsOfCategories;
    };
}
