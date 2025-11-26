cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME Framework)

set(PUBLIC_HEADERS
    Application.h
    Clock.h
    Framework.h
    RefreshRateOptions.h
    RenderableApplication.h
    SdlFramework.h   
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    Application.cpp  
    Clock.cpp
    Framework.cpp    
    RefreshRateOptions.cpp
    RenderableApplication.cpp
    SdlFramework.cpp 
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
    AppEvent
    Renderer
    Winsys
)
target_link_libraries(${TARGET_NAME} PRIVATE 
    Common
    SdlRenderer
    SDL3::SDL3
)
