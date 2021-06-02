add_library(lcd LCD.c)
include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(lcd PUBLIC .)