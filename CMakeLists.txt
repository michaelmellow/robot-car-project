cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH "/Users/michaelmellow/pico/pico-sdk")
message(STATUS "Using Pico SDK at: ${PICO_SDK_PATH}")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(robot_car_project C CXX ASM)
pico_sdk_init()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    # Add other source files here
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pico_stdlib
    hardware_pwm
    # Add other library files here
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)