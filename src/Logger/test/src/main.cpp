#include "TestLogCategory.h"

#include <Logger/LogCategoryRegistry.hpp>

#include <gtest/gtest.h>

//======================================================================================================================
int main(int argc, char** argv)
{
    logger::LogCategoryRegistry::getInstance().registerLogCategory<TestLogCategory>();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
