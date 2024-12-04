project(ProjPlatform)

file(GLOB_RECURSE PORJ_SRC_FILE "*.c")

add_library(${PROJECT_NAME} STATIC ${PORJ_SRC_FILE})

target_link_libraries(${PROJECT_NAME} PRIVATE ProjLib)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/lvgl
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
)
