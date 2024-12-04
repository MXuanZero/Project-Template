project(ProjSrc)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(SEND_ERROR "not linux platform core.")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(SEND_ERROR "not macos platform core.")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/linker.ld")
    add_subdirectory(platform/windows)
else()
    message(SEND_ERROR "not ${CMAKE_SYSTEM_NAME} platform core.")
endif()

set(EXCLUDE_DIR "platform") # 排除的目录
file(GLOB_RECURSE PORJ_SRC_FILE "*.c")
if(EXCLUDE_DIR)
    list(FILTER PORJ_SRC_FILE EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}/${EXCLUDE_DIR}/")
endif()

add_executable(${PROJECT_NAME} ${PORJ_SRC_FILE})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ProjLib}
    ${ProjPlatform}
)
