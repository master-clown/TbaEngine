cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME GuiTest)

set(SOURCES
    GuiTest.cpp
    GuiTest.h
    main.cpp
)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
target_link_libraries(${TARGET_NAME} PRIVATE 
    Common
    SdlFramework
)
