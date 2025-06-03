aux_source_directory(. TELEMETRY_SRCS)

add_library(Telemetry ${TELEMETRY_SRCS})

target_include_directories(Telemetry PUBLIC ../../include/telemetry)



target_link_libraries(Telemetry PUBLIC Devices Car Config pico_cyw43_arch_lwip_poll
)

target_include_directories(Telemetry PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/..)