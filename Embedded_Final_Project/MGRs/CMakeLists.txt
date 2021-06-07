add_subdirectory(ModeMGR)
add_subdirectory(TempMGR)
add_subdirectory(LCDManager)
target_link_libraries(ModeMGR TempMGR )