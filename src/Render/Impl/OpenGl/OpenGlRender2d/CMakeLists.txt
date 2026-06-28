cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME OpenGlRender2d)

set(PUBLIC_HEADERS
    OpenGlRenderer2d.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    OglBuffer.cpp
    OglBuffer.h
    OglGeometryBatch.cpp
    OglGeometryBatch.h
    OglGeometryBatchModifier.cpp
    OglGeometryBatchModifier.h
    OglIndexBuffer.cpp
    OglIndexBuffer.h
    OglVertexArrayObject.cpp
    OglVertexArrayObject.h
    OglVertexBuffer.cpp
    OglVertexBuffer.h
    OglVertexInfo.cpp
    OglVertexInfo.h
    OpenGlRenderer2d.cpp
    ShaderPipeline.cpp
    ShaderPipeline.h
    TypedOglBuffer.cpp
    TypedOglBuffer.h
    TypedOglBuffer.hpp
    VboRaii.cpp
    VboRaii.h
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
    OpenGlApi
    OpenGlContext
    Render2d
)
target_link_libraries(${TARGET_NAME} PRIVATE
    Content
    OpenGlTexture
    TextureStorage
)
