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
)

idf_component_register(
    SRCS
        ${files}
    INCLUDE_DIRS
        .
    REQUIRES
        ${dependencies}
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
