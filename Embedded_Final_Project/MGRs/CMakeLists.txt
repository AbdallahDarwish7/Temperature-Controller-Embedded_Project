add_subdirectory(ModeMGR)
add_subdirectory(TempMGR)
add_subdirectory(DisplayMGR)
target_link_libraries(ModeMGR TempMGR DisplayMGR)