cmake_minimum_required(VERSION 3.12)

find_package(GTest REQUIRED)

set(TARGET_NAME Render2dTest)

set(TEST_SOURCES
    GeometryBatchRenderingApp.cpp
    GeometryBatchRenderingApp.h
    Simple2dSceneTest.cpp
    TextureSamplingTest.cpp
)
list(TRANSFORM TEST_SOURCES PREPEND "src/")

set(TEST_RESOURCES
    container.jpg
)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE 
    GuiAppTemplate
    OpenGlContext
    Render2d
    SdlFramework
    SdlRenderContext
    Texture
    TextureLoader
    GTest::gtest_main)

#=======================================================================================================================
# Copy resource files
list(TRANSFORM TEST_RESOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/resources/")
set(RESOURCES_TARGET_FOLDER "$<TARGET_FILE_DIR:${TARGET_NAME}>/resources/")
add_custom_target(CopyResourceFilesTarget
    ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${RESOURCES_TARGET_FOLDER}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_newer ${TEST_RESOURCES} "${RESOURCES_TARGET_FOLDER}"
    VERBATIM
)
add_dependencies(CopyResourceFilesTarget ${TARGET_NAME})

#=======================================================================================================================
include(GoogleTest)
gtest_discover_tests(${TARGET_NAME} PROPERTIES LABELS "ManualGuiTests")
