SET(LIB_NAME PWM)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} PWM.c)
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})