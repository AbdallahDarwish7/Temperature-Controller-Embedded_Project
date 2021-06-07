SET(LIB_NAME Calibrator)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} Calibrator_Resistor.c)
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})