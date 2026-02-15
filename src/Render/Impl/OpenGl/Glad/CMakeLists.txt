cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Glad)

set(PUBLIC_HEADERS
    KHR/khrplatform.h
    glad/glad.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    glad.c
)
list(TRANSFORM SOURCES PREPEND "src/")

add_library(${TARGET_NAME} STATIC)
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE C)

target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
target_sources(${TARGET_NAME} 
    PUBLIC 
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
    ${PUBLIC_HEADERS})
