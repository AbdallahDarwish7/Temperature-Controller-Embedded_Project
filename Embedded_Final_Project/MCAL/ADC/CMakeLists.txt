SET(LIB_NAME ADC)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} ADC.c)
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})