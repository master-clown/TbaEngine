cmake_minimum_required(VERSION 3.12)

find_package(GTest REQUIRED)

set(TARGET_NAME InputTests)

set(TEST_SOURCES
    KeyboardEventsTest.cpp
)
list(TRANSFORM TEST_SOURCES PREPEND "src/")

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE 
    AppEvent
    EventInfo
    GuiAppTemplate
    InputEvent
    Logger
    SdlFramework
    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME} PROPERTIES LABELS "ManualGuiTests")
