add_library(keypad KeyPad.c)
include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(keypad PUBLIC .)