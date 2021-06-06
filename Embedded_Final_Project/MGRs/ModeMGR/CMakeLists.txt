set(LIB_NAME ModeMGR)
add_library(${LIB_NAME} Mode_MGR.c Mode_MGR.h)
include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})