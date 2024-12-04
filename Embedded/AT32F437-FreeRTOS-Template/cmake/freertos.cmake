# FreeRTOS portable
set(FREERTOS_PORT GCC_ARM_CM4F)
set(FREERTOS_HEAP 4)
add_library(freertos_config INTERFACE)
target_include_directories(
    freertos_config
    SYSTEM
    INTERFACE
    ${CMAKE_SOURCE_DIR}/lib/config
)
target_compile_definitions(
    freertos_config
    INTERFACE
    projCOVERAGE_TEST=0
)