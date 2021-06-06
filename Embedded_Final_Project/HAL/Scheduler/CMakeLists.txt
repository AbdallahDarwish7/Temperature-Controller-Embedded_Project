SET(LIB_NAME Scheduler)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} Scheduler.c)
target_include_directories(${LIB_NAME} PUBLIC .)