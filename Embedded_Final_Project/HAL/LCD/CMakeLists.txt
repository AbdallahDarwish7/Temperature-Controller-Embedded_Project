set(LIB_NAME LCD)
add_library(${LIB_NAME} LCD.c LCD_Cfg.c)
include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})