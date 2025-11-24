cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Geometry2d)

set(PUBLIC_HEADERS
    ContentTraits.h
    Line.h
    Point2d.h
    ScreenCoordinate.h
    Triangle.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    ContentTraits.cpp
    Line.cpp
    Point2d.cpp
    ScreenCoordinate.cpp
    Triangle.cpp
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
    Content
)
target_link_libraries(${TARGET_NAME} PRIVATE 
    Common
)
