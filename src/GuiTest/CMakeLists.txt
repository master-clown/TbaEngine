cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME GuiTest)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME})

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
