#pragma once

#include <concepts>
#include <string>
#include <type_traits>

//======================================================================================================================
namespace logger {
    template <class LogCategory>
    concept LogCategoryConcept = requires(LogCategory cat) {
        //--------------------------------------------------------------------------------------------------------------
        std::is_enum_v<LogCategory>;

        //--------------------------------------------------------------------------------------------------------------
        { str(cat) } -> std::same_as<std::string>;
        { begin(cat) } -> std::same_as<LogCategory>;
        { end(cat) } -> std::same_as<LogCategory>;
        { operator++(cat) } -> std::same_as<LogCategory>;
        { operator*(cat) } -> std::same_as<LogCategory>;
    };
}
