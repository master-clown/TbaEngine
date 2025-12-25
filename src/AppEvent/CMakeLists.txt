cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME AppEvent)

set(PUBLIC_HEADERS
    AppEvent.h          
    AppEventMgr.h       
    EventInfo.h         
    EventInfo.hpp       
    EventQueue.h 
    SdlAppEventMgr.h      
    WindowEvent.h       
    WindowEventDetails.h
    WindowEventKind.h   
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    AppEvent.cpp          
    AppEventMgr.cpp       
    EventInfo.cpp         
    EventQueue.cpp
    SdlAppEventMgr.cpp    
    WindowEvent.cpp       
    WindowEventDetails.cpp
    WindowEventKind.cpp   
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
target_link_libraries(${TARGET_NAME} PRIVATE 
    Common
    SDL3::SDL3
)
