#include "TestLogCategory.h"

#include <Logger/CategorizedLogging.h>

#include <gtest/gtest.h>

#include <sstream>

//======================================================================================================================
namespace {
    using MsgLevel = logger::LogMessageLevel;

    constexpr auto logRecordSeparator = "\n";

    struct TestLog final {
        std::ostringstream logSstream;
        std::ostringstream errorLogSstream;

        TestLog()
        {
            logger::LoggingSettings::setLoggingStream(&logSstream);
            logger::LoggingSettings::setErrorLoggingStream(&errorLogSstream);
        }

        ~TestLog()
        {
            logger::LoggingSettings::setLoggingStream();
            logger::LoggingSettings::setErrorLoggingStream();
        }
    };
}

//======================================================================================================================
#define TEST_CASE(name) TEST(LogCategoryTest, name)

//======================================================================================================================
TEST_CASE(PrintToCategoryWithSilentLevel)
{
    using ShouldPrint = bool;

    TestLog testLog;
    logger::LogCategoryRegistry::getInstance().setLogLevel(TestLogCategory::One, logger::LogMessageLevel::Silent);

    const auto checkLevel = [&testLog](const ShouldPrint shouldPrint, const MsgLevel msgLevel) {
        const auto text = "Log " + str(msgLevel);
        const auto expected = text + logRecordSeparator;
        LOG_CATEGORIZED(TestLogCategory::One, msgLevel, text);
        EXPECT_EQ(testLog.logSstream.str(), shouldPrint ? expected : "");
        testLog.logSstream.str("");
    };

    checkLevel(ShouldPrint{false}, MsgLevel::Silent);
    checkLevel(ShouldPrint{false}, MsgLevel::Brief);
    checkLevel(ShouldPrint{false}, MsgLevel::Normal);
    checkLevel(ShouldPrint{false}, MsgLevel::Verbose);
    checkLevel(ShouldPrint{false}, MsgLevel::Trace);
}

//======================================================================================================================
TEST_CASE(PrintToCategoryWithBriefLevel)
{
    using ShouldPrint = bool;

    TestLog testLog;
    logger::LogCategoryRegistry::getInstance().setLogLevel(TestLogCategory::One, logger::LogMessageLevel::Brief);

    const auto checkLevel = [&testLog](const ShouldPrint shouldPrint, const MsgLevel msgLevel) {
        const auto text = "Log " + str(msgLevel);
        const auto expected = text + logRecordSeparator;
        LOG_CATEGORIZED(TestLogCategory::One, msgLevel, text);
        EXPECT_EQ(testLog.logSstream.str(), shouldPrint ? expected : "");
        testLog.logSstream.str("");
    };

    checkLevel(ShouldPrint{false}, MsgLevel::Silent);
    checkLevel(ShouldPrint{true}, MsgLevel::Brief);
    checkLevel(ShouldPrint{false}, MsgLevel::Normal);
    checkLevel(ShouldPrint{false}, MsgLevel::Verbose);
    checkLevel(ShouldPrint{false}, MsgLevel::Trace);
}

//======================================================================================================================
TEST_CASE(PrintToCategoryWithNormalLevel)
{
    using ShouldPrint = bool;

    TestLog testLog;
    logger::LogCategoryRegistry::getInstance().setLogLevel(TestLogCategory::One, logger::LogMessageLevel::Normal);

    const auto checkLevel = [&testLog](const ShouldPrint shouldPrint, const MsgLevel msgLevel) {
        const auto text = "Log " + str(msgLevel);
        const auto expected = text + logRecordSeparator;
        LOG_CATEGORIZED(TestLogCategory::One, msgLevel, text);
        EXPECT_EQ(testLog.logSstream.str(), shouldPrint ? expected : "");
        testLog.logSstream.str("");
    };

    checkLevel(ShouldPrint{false}, MsgLevel::Silent);
    checkLevel(ShouldPrint{true}, MsgLevel::Brief);
    checkLevel(ShouldPrint{true}, MsgLevel::Normal);
    checkLevel(ShouldPrint{false}, MsgLevel::Verbose);
    checkLevel(ShouldPrint{false}, MsgLevel::Trace);
}

//======================================================================================================================
TEST_CASE(PrintToCategoryWithVerboseLevel)
{
    using ShouldPrint = bool;

    TestLog testLog;
    logger::LogCategoryRegistry::getInstance().setLogLevel(TestLogCategory::One, logger::LogMessageLevel::Verbose);

    const auto checkLevel = [&testLog](const ShouldPrint shouldPrint, const MsgLevel msgLevel) {
        const auto text = "Log " + str(msgLevel);
        const auto expected = text + logRecordSeparator;
        LOG_CATEGORIZED(TestLogCategory::One, msgLevel, text);
        EXPECT_EQ(testLog.logSstream.str(), shouldPrint ? expected : "");
        testLog.logSstream.str("");
    };

    checkLevel(ShouldPrint{false}, MsgLevel::Silent);
    checkLevel(ShouldPrint{true}, MsgLevel::Brief);
    checkLevel(ShouldPrint{true}, MsgLevel::Normal);
    checkLevel(ShouldPrint{true}, MsgLevel::Verbose);
    checkLevel(ShouldPrint{false}, MsgLevel::Trace);
}

//======================================================================================================================
TEST_CASE(PrintToCategoryWithTraceLevel)
{
    using ShouldPrint = bool;

    TestLog testLog;
    logger::LogCategoryRegistry::getInstance().setLogLevel(TestLogCategory::One, logger::LogMessageLevel::Trace);

    const auto checkLevel = [&testLog](const ShouldPrint shouldPrint, const MsgLevel msgLevel) {
        const auto text = "Log " + str(msgLevel);
        const auto expected = text + logRecordSeparator;
        LOG_CATEGORIZED(TestLogCategory::One, msgLevel, text);
        EXPECT_EQ(testLog.logSstream.str(), shouldPrint ? expected : "");
        testLog.logSstream.str("");
    };

    checkLevel(ShouldPrint{false}, MsgLevel::Silent);
    checkLevel(ShouldPrint{true}, MsgLevel::Brief);
    checkLevel(ShouldPrint{true}, MsgLevel::Normal);
    checkLevel(ShouldPrint{true}, MsgLevel::Verbose);
    checkLevel(ShouldPrint{true}, MsgLevel::Trace);
}
