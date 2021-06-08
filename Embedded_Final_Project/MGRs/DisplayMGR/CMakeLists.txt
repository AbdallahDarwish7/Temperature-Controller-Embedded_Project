SET(LIB_NAME DisplayMGR)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} Display_MGR.c)
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})