cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(Pico_ePaper_Code)
pico_sdk_init()

# Add compilation subdirectory
add_subdirectory(lib/standard_pico_lib/Config)
add_subdirectory(lib/standard_pico_lib/Devices)

add_subdirectory(src/car)
add_subdirectory(src/telemetry)
add_subdirectory(tests)
#add_subdirectory(examples)

# Add header file directory
#include_directories(examples)
include_directories(./lib/standard_pico_lib/Config)
include_directories(./lib/standard_pico_lib/Devices)

include_directories(./include/car)
include_directories(./include/telemetry)
include_directories(./tests)

# Generate executable file
add_executable(main 
main.cpp
)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

target_link_libraries(main Car Telemetry Test Config pico_stdlib Devices hardware_i2c)
