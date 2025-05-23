cmake_minimum_required(VERSION 3.16.3)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/sdkconfig)
    message(FATAL_ERROR "sdkconfig not found")
endif()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config.cmake)
    message(FATAL_ERROR "config.cmake not found")
endif()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build)
    message(FATAL_ERROR "Build folder not found. Please run './switchconf.sh' first.")
endif()

if (NOT IS_SYMLINK ${CMAKE_CURRENT_SOURCE_DIR}/build)
    message(FATAL_ERROR "Build folder is not a symlink. Please run './switchconf.sh' first.")
endif()

include(config.cmake)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions(-DASIO_DISABLE_CONCEPTS=1)

add_definitions(-DFASTLED_ESP32_FLASH_LOCK=1)

set(EXTRA_COMPONENT_DIRS
    esp-protocols/components
    components/esp-idf-lib/components
)

project(${APP_NAME})

set(expected_build_folder "${CMAKE_CURRENT_SOURCE_DIR}/build")
