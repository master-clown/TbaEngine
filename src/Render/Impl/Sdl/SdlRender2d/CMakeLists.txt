cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME SdlRender2d)

set(PUBLIC_HEADERS
    SdlRenderer2d.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    Details/SdlTriangle.cpp
    Details/SdlTriangle.h
    Details/PrimitiveVariant.cpp
    Details/PrimitiveVariant.h
    SdlGeometryBatch.cpp
    SdlGeometryBatch.h
    SdlGeometryBatchModifier.cpp
    SdlGeometryBatchModifier.h
    SdlRenderer2d.cpp
)
list(TRANSFORM SOURCES PREPEND "src/")

find_package(SDL3 REQUIRED)

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
    Render2d
)
target_link_libraries(${TARGET_NAME} PRIVATE
    Content
    SdlWinsys
    SDL3::SDL3
)
