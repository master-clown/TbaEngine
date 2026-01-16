cmake_minimum_required(VERSION 3.12)

find_package(GTest REQUIRED)

set(TARGET_NAME LoggerUnitTests)

set(SOURCES
    TestLogCategory.cpp
    TestLogCategory.h
    main.cpp
)
list(TRANSFORM SOURCES PREPEND "src/")

set(TEST_SOURCES
    LogCategoryTest.cpp
    LogTest.cpp
)
list(TRANSFORM TEST_SOURCES PREPEND "src/")

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${SOURCES} ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE 
    Logger
    GTest::gtest)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME} PROPERTIES LABELS "UnitTests")
