cmake_minimum_required(VERSION 3.12)

find_package(GTest REQUIRED)

set(TARGET_NAME RenderSceneTest)

set(TEST_SOURCES
    RenderablesIn2dTest.cpp
    TestApp.cpp
    TestApp.h
)
list(TRANSFORM TEST_SOURCES PREPEND "src/")

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE 
    GuiAppTemplate
    InputEvent
    OpenGlContext
    Render2d
    RenderScene
    SdlFramework
    GTest::gtest_main)

#=======================================================================================================================
include(GoogleTest)
gtest_discover_tests(${TARGET_NAME} PROPERTIES LABELS "ManualGuiTests")
