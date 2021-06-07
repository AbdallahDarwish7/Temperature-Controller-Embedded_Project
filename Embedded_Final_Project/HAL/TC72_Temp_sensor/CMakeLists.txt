add_library(TC72 TC72.c)
include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(TC72 PUBLIC . ${CMAKE_SOURCE_DIR})