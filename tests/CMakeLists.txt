aux_source_directory(. TEST_SRCS)

add_library(Test ${TEST_SRCS})

target_include_directories(Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include/car)


target_link_libraries(Test PUBLIC Car Devices Config)