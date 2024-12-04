project(ProjLib)

include(${CMAKE_SOURCE_DIR}/cmake/freertos.cmake)
add_subdirectory(freertos)

set(EXCLUDE_DIR "cmsis/dsp") # 排除的目录
file(GLOB_RECURSE 
    PORJ_LIB_FILE 
    "cmsis/cm4/device_support/startup/gcc/startup_at32f435_437.s"
    "at32f437/*.c"
    "cmsis/*.c"
)
if(EXCLUDE_DIR)
    list(FILTER PORJ_LIB_FILE EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}/${EXCLUDE_DIR}/")
endif()

add_library(${PROJECT_NAME} STATIC)

target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    freertos_kernel
)


target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/cm4/core_support
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/cm4/device_support
    ${CMAKE_CURRENT_SOURCE_DIR}/at32f437/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/config
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${PORJ_LIB_FILE}
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
)

if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()