aux_source_directory(. CAR_SRCS)

add_library(Car ${CAR_SRCS})

target_include_directories(Car PUBLIC ../../include/car)

target_link_libraries(Car PUBLIC Devices)