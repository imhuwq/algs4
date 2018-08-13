include_directories("common")
include_directories("../includes/sort")
include_directories("../includes/search")

file(GLOB_RECURSE RUN_CASES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach (RUN_CASE ${RUN_CASES})
    get_filename_component(CASE_NAME ${RUN_CASE} NAME_WE)
    add_executable(${CASE_NAME} ${RUN_CASE})
endforeach ()