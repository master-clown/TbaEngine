cmake_minimum_required(VERSION 3.12)

find_package(SDL3 REQUIRED)

set(TARGET_NAME SdlWinsys)

set(PUBLIC_HEADERS
    SdlWindow.h    
    SdlWindowMgr.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    SdlWindow.cpp   
    SdlWindowMgr.cpp
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
    EventSys
    Winsys
)
target_link_libraries(${TARGET_NAME} PRIVATE
    EventInfo
    SdlEventSys
    WinEvent
    SDL3::SDL3
)
