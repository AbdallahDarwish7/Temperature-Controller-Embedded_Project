add_subdirectory(TC72_Temp_sensor)
add_subdirectory(LCD)
add_subdirectory(KeyPad)
target_link_libraries(KeyPad LCD)
