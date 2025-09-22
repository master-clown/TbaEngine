cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME GuiTest)

set(SOURCES
    main.cpp
)

find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE SDL3::SDL3)
