cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Common)

set(PUBLIC_HEADERS
    Memory.h
    String.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    ${PUBLIC_HEADERS}
    src/Memory.cpp
    src/String.cpp
)

add_library(${TARGET_NAME} STATIC)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
