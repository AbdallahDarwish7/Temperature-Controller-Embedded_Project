SET(LIB_NAME SPI)
include_directories(${CMAKE_SOURCE_DIR})
add_library(${LIB_NAME} SPI.c )
target_include_directories(${LIB_NAME} PUBLIC .)