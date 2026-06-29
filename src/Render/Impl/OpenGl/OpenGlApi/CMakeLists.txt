cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME OpenGlApi)

set(PUBLIC_HEADERS
    ErrorCheck.h
    GpuOperationsCompletedEvent.h
    OpenGlApi.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    ErrorCheck.cpp
    GpuOperationsCompletedEvent.cpp
    OpenGlApi.cpp
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
    Glad
)
target_link_libraries(${TARGET_NAME} PRIVATE
    Logger
)
