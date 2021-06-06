set(LIB_NAME KeyPad)
add_library(${LIB_NAME} KeyPad.c KeyPad_Cfg.c)
include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})