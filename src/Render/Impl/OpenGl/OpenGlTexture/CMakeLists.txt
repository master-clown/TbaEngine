cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME OpenGlTexture)

set(PUBLIC_HEADERS
    OpenGlTexture.h
    OpenGlTextureId.h
    OpenGlTextureHandle.h
    OpenGlTexturingMgr.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    OglTextureHandleRaii.cpp
    OglTextureHandleRaii.h
    OglTextureHandles.cpp
    OglTextureHandles.h
    OglTextureSampler.cpp
    OglTextureSampler.h
    OglTexturingObjectsCreator.cpp
    OglTexturingObjectsCreator.h
    OpenGlTexture.cpp
    OpenGlTextureId.cpp
    OpenGlTextureHandle.cpp
    OpenGlTexturingMgr.cpp
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
    Texture
)
