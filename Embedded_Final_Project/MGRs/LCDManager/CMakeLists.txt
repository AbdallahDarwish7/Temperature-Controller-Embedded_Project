SET(LIB_NAME LCDManager)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} LCD_Manager.c)
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})