set(LIB_NAME TempMGR)
add_library(${LIB_NAME} Temp_MGR.c  )
include_directories(${CMAKE_SOURCE_DIR})
target_include_directories(${LIB_NAME} PUBLIC . ${CMAKE_SOURCE_DIR})