cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Logger)

set(PUBLIC_HEADERS
    Logging.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    Logging.cpp
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
