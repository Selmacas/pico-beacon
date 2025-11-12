# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_BUILD_TYPE "Release") 

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
# include (pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(pico-beacon C CXX ASM)

pico_sdk_init()
add_executable(pico-beacon)
pico_generate_pio_header(pico-beacon ${CMAKE_CURRENT_LIST_DIR}/pico-hf-oscillator/piodco/dco2.pio)

target_sources(pico-beacon PUBLIC
	             ${CMAKE_CURRENT_LIST_DIR}/pico-hf-oscillator/lib/assert.c
               ${CMAKE_CURRENT_LIST_DIR}/pico-hf-oscillator/piodco/piodco.c
               ${CMAKE_CURRENT_LIST_DIR}/main.c
              )

pico_set_program_name(pico-beacon "pico-beacon")
pico_set_program_version(pico-beacon "0.5")

pico_enable_stdio_uart(pico-beacon 1)
pico_enable_stdio_usb(pico-beacon 1)

# Add the standard include files to the build
target_include_directories(pico-beacon PRIVATE
                           ${CMAKE_CURRENT_LIST_DIR}
                           ${CMAKE_CURRENT_LIST_DIR}/pico-hf-oscillator/piodco
                           ${CMAKE_CURRENT_LIST_DIR}/pico-hf-oscillator/debug
                           ${CMAKE_CURRENT_LIST_DIR}/pico-hf-oscillator
                           ${CMAKE_CURRENT_LIST_DIR}/..
                          )

target_link_libraries(pico-beacon
                      pico_stdlib
                      pico_sync
                      pico_multicore
                      hardware_timer
                      hardware_clocks
                      hardware_pio
                     )

pico_add_extra_outputs(pico-beacon)
