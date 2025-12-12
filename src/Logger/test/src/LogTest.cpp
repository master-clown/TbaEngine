#include "TestLogCategory.h"

#include <Logger/BasicLogging.h>

#include <gtest/gtest.h>

#include <sstream>

//======================================================================================================================
namespace {
    constexpr auto logRecordSeparator = "\n";

    struct TestLog final {
        std::ostringstream logSstream;
        std::ostringstream errorLogSstream;

        TestLog()
        {
            logger::setLoggingStream(&logSstream);
            logger::setErrorLoggingStream(&errorLogSstream);
        }

        ~TestLog()
        {
            logger::setLoggingStream(std::nullopt);
            logger::setErrorLoggingStream(std::nullopt);
        }
    };
}

//======================================================================================================================
#define TEST_CASE(name) TEST(LogTest, name)

//======================================================================================================================
TEST_CASE(DifferentStreamsRemainSeparateOnPrintLog)
{
    TestLog testLog;
    constexpr auto text = "Some text";
    const auto expected = std::string{text} + logRecordSeparator;

    LOG_ALWAYS(text);

    EXPECT_EQ(testLog.logSstream.str(), expected);
    EXPECT_EQ(testLog.errorLogSstream.str(), "");
}

//======================================================================================================================
TEST_CASE(DifferentStreamsRemainSeparateOnPrintErrorLog)
{
    TestLog testLog;
    constexpr auto text = "Some text";
    const auto expected = std::string{"[ERROR] "} + text + logRecordSeparator;

    LOG_ERROR(text);

    EXPECT_EQ(testLog.logSstream.str(), "");
    EXPECT_EQ(testLog.errorLogSstream.str(), expected);
}

//======================================================================================================================
TEST_CASE(SameStreamsHaveSameText)
{
    std::ostringstream sstream;
    constexpr auto text = "Some text";
    constexpr auto errorText = "Error text";

    logger::setLoggingStream(&sstream);
    logger::setErrorLoggingStream(&sstream);

    LOG_ALWAYS(text);
    LOG_ERROR(errorText);

    EXPECT_EQ(sstream.str(), std::string{text} + logRecordSeparator + "[ERROR] " + errorText + logRecordSeparator);
}

//======================================================================================================================
TEST_CASE(FormattedLogIsEssentiallyEquivalentToStreamBased)
{
    std::ostringstream sstreamForStreamedPrint;
    std::ostringstream sstreamForFormattedPrint;
    const auto userName = "UserName";

    logger::setLoggingStream(&sstreamForStreamedPrint);
    LOG_ALWAYS("Hello, " << userName << ", you are always " << 25 << "!");

    logger::setLoggingStream(&sstreamForFormattedPrint);
    LOG_ALWAYS("Hello, {}, you are always {}!", userName, 25);

    EXPECT_EQ(sstreamForStreamedPrint.str(), sstreamForFormattedPrint.str());
}
