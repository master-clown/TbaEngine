cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME TextureLoader)

set(PUBLIC_HEADERS
    TextureLoader.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    TextureLoader.cpp
    stb_image.h
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
    Texture
)
target_link_libraries(${TARGET_NAME} PRIVATE 
    Common
)
