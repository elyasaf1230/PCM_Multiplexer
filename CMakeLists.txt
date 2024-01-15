cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pcm_multiplexer)

pico_sdk_init()

add_executable(main
	main.c
)

target_link_libraries(main pico_stdlib pico_multicore)

pico_add_extra_outputs(main)
