cmake_minimum_required(VERSION 3.12)

find_package(SDL3 REQUIRED)

set(TARGET_NAME SdlInput)

set(PUBLIC_HEADERS
    SdlDeviceMgr.h
    SdlKeyboard.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    SdlDeviceMgr.cpp
    SdlKeyboard.cpp
    SdlKeyboardState.cpp
    SdlKeyboardState.h
    SdlKeyScancode.cpp
    SdlKeyScancode.h
)
list(TRANSFORM SOURCES PREPEND "src/")

add_library(${TARGET_NAME} STATIC)

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
target_sources(${TARGET_NAME}
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
    ${PUBLIC_HEADERS})
target_link_libraries(${TARGET_NAME} PUBLIC
    Input
)
target_link_libraries(${TARGET_NAME} PRIVATE
    Common
    Logger
    SDL3::SDL3
)
