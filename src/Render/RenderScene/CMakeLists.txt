cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME RenderScene)

set(PUBLIC_HEADERS
    GeometryChunk2d.h
    RenderScene.h
    Renderable.h
    Renderable2d.h
    RenderableBlueprint.h
    TracedGeometryBatchModifier2d.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    GeometryChunk2d.cpp
    RenderScene.cpp
    Renderable.cpp
    Renderable2d.cpp
    RenderableBlueprint.cpp
    TracedGeometryBatchModifier2d.cpp
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
    Geometry2d
    Render2d
)
target_link_libraries(${TARGET_NAME} PRIVATE 
    Common
)
