cmake_minimum_required(VERSION 3.5)

set(FAMILY "rp2040")
set(FORCE_TEST 0) # 1 for test
set(PICO_TINYUSB_NO_EXAMPLE_WARNINGS 1)
include($ENV{PICO_SDK_PATH}/lib/tinyusb/hw/bsp/family_support.cmake)

# gets PROJECT name for the example (e.g. <BOARD>-<DIR_NAME>)
family_get_project_name(PROJECT ${CMAKE_CURRENT_LIST_DIR})

project(${PROJECT})

# Checks this example is valid for the family and initializes the project
family_initialize_project(${PROJECT} ${CMAKE_CURRENT_LIST_DIR})

add_executable(${PROJECT})

if (FORCE_TEST)
target_compile_definitions(${PROJECT} PRIVATE
  CFG_EXAMPLE_VIDEO_TEST
)
endif()

# Example source
target_sources(${PROJECT} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_descriptors.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ov7670/ov7670.c
)

# Example include
target_include_directories(${PROJECT} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ov7670
)

pico_generate_pio_header(${PROJECT}  ${CMAKE_CURRENT_LIST_DIR}/src/ov7670/image.pio)

target_link_libraries(${PROJECT} PUBLIC
	pico_stdlib
	hardware_dma
	hardware_i2c
	hardware_pio
	hardware_pwm
)
# disable usb output, enable uart output
pico_enable_stdio_usb(${PROJECT}  0)
pico_enable_stdio_uart(${PROJECT}  1)
# Configure compilation flags and libraries for the example... see the corresponding function
# in hw/bsp/FAMILY/family.cmake for details.
family_configure_device_example(${PROJECT})