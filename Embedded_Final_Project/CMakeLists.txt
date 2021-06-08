CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
SET(CMAKE_SYSTEM_NAME Generic)
SET(AVRBIN /home/abdallah/avr8-gnu-toolchain/bin)          # change compiler path
SET(AVROBJCOPY avr-objcopy)
SET(AVRSIZE avr-size)
SET(AVRDUDE avrdude)
#*******************************************************************************
SET(PROGRAMMER usbasp)                                     # <-- Programmertype
SET(PORT usb)                                              # <-- USB or interface e.g. /dev/cu.usbserial ....
#SET(BAUD 57600)	        	                           # <-- transfer rate

SET(EEPROM NO)                                             # <-- should an x.eep file be created?
SET(FLASH NO)                                              # <-- should be flashed?

#============================================================================================

SET(CMAKE_C_COMPILER ${AVRBIN}/avr-gcc)
SET(CMAKE_CXX_COMPILER ${AVRBIN}/avr-g++)
#============================================================================================
PROJECT(Embedded_Final_Project)                                          # <-- Prjectname

SET(SOURCE_FILES main.c Macros.h typedefs.h)                                          # <-- Source file(s)

SET(DEVICE atmega32)                                       # <-- MCU
SET(F_CPU 8000000)                                         # <-- MCU-Frequency

#*******************************************************************************


SET(CMAKE_C_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${F_CPU}UL -std=gnu99 -Wl,--gc-sections")
SET(CMAKE_CXX_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${F_CPU}UL -Wl,--gc-sections")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_PREFIX_PATH /home/abdallah/avr8-gnu-toolchain/avr)                  # change compiler path
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.eep"
        )

include_directories(/home/abdallah/avr8-gnu-toolchain/avr/include)           # change compiler path

#============================================================================================

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(MCAL)
add_subdirectory(HAL)
add_subdirectory(MGRs)
target_link_libraries(TC72 SPI)
target_link_libraries(ModeMGR PWM Scheduler)
target_link_libraries(TempMGR TC72)
target_link_libraries(LCD DIO)
target_link_libraries(KeyPad DIO DisplayMGR)
target_link_libraries(Scheduler Timer)
target_link_libraries(TempMGR TC72)
target_link_libraries(ModeMGR Timer Calibrator)
target_link_libraries(Calibrator ADC)
target_link_libraries(DisplayMGR LCD Scheduler KeyPad)
target_link_libraries(${CMAKE_PROJECT_NAME} TC72 Timer KeyPad TempMGR ModeMGR Scheduler DisplayMGR)


ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${AVRBIN}/${AVROBJCOPY} -O ihex -R .eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex)

if (EEPROM)
    ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${AVRBIN}/${AVROBJCOPY} -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.eep)
endif (EEPROM)

ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${AVRBIN}/${AVRSIZE} --target=ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex)

if (FLASH)
    ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND /usr/bin/${AVRDUDE} -p${DEVICE} -c${PROGRAMMER} -P${PORT} -b${BAUD} -U flash:w:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex)
    # -U lfuse:w:your_value:m
    # -U hfuse:w:your_value:m
endif (FLASH)