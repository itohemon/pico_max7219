cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(eyes C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(eyes
  eyes.c
  )

# pull in common dependencies
target_link_libraries(eyes pico_stdlib hardware_spi)

# create map/bin/hex file etc.
pico_add_extra_outputs(eyes)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

