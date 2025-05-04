file(
    GLOB_RECURSE files
        *.h
        *.cpp
        *.c
)

set(dependencies
        ArduinoJson
        FastLED-idf
        TFT_eSPI
        app_update
        arduino-esp32
        cpputils
        esp-gui-lib
        esp_app_format
        esp_system
        espchrono
        espconfiglib
        espcpputils
        espfontlib
        esphttpdutils
        esptftlib
        espwifistack
        freertos
        mdns
        sunset-idf
        ads111x
        pca9685
)

# generate all the icons during build-time
file(GLOB_RECURSE icons
    ${CMAKE_CURRENT_SOURCE_DIR}/../icons/*.png
)

# create a folder for the generated icons
set(generated_icons_path "${CMAKE_CURRENT_BINARY_DIR}/generated/icons")

file(MAKE_DIRECTORY ${generated_icons_path})

set(generated_icons "")

# for every icon, there will be a corresponding .h and .cpp file. there will also be a <icon_name>_grey.h / .cpp file with background
# the script ${CMAKE_CURRENT_SOURCE_DIR}/../convert-icons.sh will generate all of the files with a single command
foreach(icon ${icons})
    get_filename_component(icon_name ${icon} NAME_WE)
    set(icon_path "${CMAKE_CURRENT_BINARY_DIR}/generated/icons/${icon_name}")
    set(icon_cpp "${icon_path}.cpp")
    set(icon_h "${icon_path}.h")
    set(icon_grey_cpp "${icon_path}_grey.cpp")
    set(icon_grey_h "${icon_path}_grey.h")
    list(APPEND files ${icon_cpp} ${icon_h} ${icon_grey_cpp} ${icon_grey_h})
    list(APPEND generated_icons ${icon_cpp} ${icon_h} ${icon_grey_cpp} ${icon_grey_h})
endforeach()

idf_component_register(
    SRCS
        ${files}
    INCLUDE_DIRS
        .
        ${CMAKE_CURRENT_BINARY_DIR}/generated
    REQUIRES
        ${dependencies}
)

message(STATUS "Generated icons path: ${generated_icons_path}")

message(STATUS "Generated icons: ${generated_icons}")

# generate the icons
add_custom_command(
    OUTPUT
        ${generated_icons}
    COMMAND
        ${CMAKE_CURRENT_SOURCE_DIR}/../convert-icons.sh -o ${generated_icons_path}
    DEPENDS
        ${icons}
        ${CMAKE_CURRENT_SOURCE_DIR}/../convert-icons.sh
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/..
    COMMENT
        "Generating icons..."
)

execute_process(
    COMMAND git describe --tags --always
    WORKING_DIRECTORY ${COMPONENT_DIR}/..
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_compile_options(${COMPONENT_TARGET}
    PRIVATE
        -fstack-reuse=all
        -fstack-protector-all
        -fdiagnostics-color=always
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-parentheses
        -DVERSION=\"${GIT_VERSION}\"
        -DAPP_NAME=\"${APP_NAME}\"
)
