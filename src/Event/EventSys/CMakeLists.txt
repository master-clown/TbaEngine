cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME EventSys)

set(PUBLIC_HEADERS
    EventMgr.h       
    EventQueue.h 
    LogCategory.h
    NativeEvent.h
    NativeEventListenerId.h
    NativeEventListener.h
    NativeEventListeners.h
)
list(TRANSFORM PUBLIC_HEADERS PREPEND "include/${TARGET_NAME}/")

set(SOURCES
    EventMgr.cpp       
    EventQueue.cpp
    LogCategory.cpp
    NativeEvent.cpp
    NativeEventListenerId.cpp
    NativeEventListener.cpp
    NativeEventListeners.cpp
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
    AppEvent
    Common
)
target_link_libraries(${TARGET_NAME} PRIVATE 
    Logger
)
