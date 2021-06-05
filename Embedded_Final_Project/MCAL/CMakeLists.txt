add_subdirectory(DIO)
add_subdirectory(SPI)
add_subdirectory(Timer)
target_link_libraries(SPI DIO)