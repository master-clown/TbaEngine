#pragma once

#include <Logger/BasicLogging.h>
#include <Logger/LogCategoryRegistry.hpp>
#include <Logger/LogMessageLevel.h>

//======================================================================================================================
// private macros
#define _SHOULD_LOG(logMsgCategory, logMsgLevel)                                              \
    (logMsgLevel <= logger::LogCategoryRegistry::getInstance().getLogLevel(logMsgCategory) && \
     logMsgLevel != logger::LogMessageLevel::Silent)

//======================================================================================================================
#define LOG_CATEGORIZED(logMsgCategory, logMsgLevel, ...)     \
    {                                                         \
        if (_SHOULD_LOG(logMsgCategory, logMsgLevel)) {       \
            _LOG_IMPL_WITH_FORMATTING_SELECTION(__VA_ARGS__); \
        }                                                     \
    }

