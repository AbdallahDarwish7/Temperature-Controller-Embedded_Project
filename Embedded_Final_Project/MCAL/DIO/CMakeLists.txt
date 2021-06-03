SET(LIB_NAME DIO)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} DIO.c DIO_Cfg.c)
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})