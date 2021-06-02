add_subdirectory(DIO)
add_subdirectory(SPI)
target_link_libraries(SPI DIO)