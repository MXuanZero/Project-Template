project(ProjLib)

set(EXCLUDE_DIR "") # 排除的目录
file(GLOB_RECURSE PORJ_LIB_FILE "*.c")
if(EXCLUDE_DIR)
    list(FILTER PORJ_LIB_FILE EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}/${EXCLUDE_DIR}/")
endif()

add_library(${PROJECT_NAME} STATIC ${PORJ_LIB_FILE})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ProjPlatform}
)
