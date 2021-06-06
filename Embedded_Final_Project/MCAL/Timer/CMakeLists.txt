SET(LIB_NAME Timer)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} Timer.c)
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})