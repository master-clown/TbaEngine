cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Keyboard)

set(PUBLIC_HEADERS
    KeyCode.h
    KeyMods.h
    KeyScancode.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    KeyCode.cpp
    KeyMods.cpp
    KeyScancode.cpp
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
    Common
)
