file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.hpp")

add_library(sc-kpm-common SHARED ${SOURCES} ${HEADERS})

include_directories("${SC_KPM_ROOT}/common" ${SC_MEMORY_SRC} ${GLIB2_INCLUDE_DIRS})
add_dependencies(sc-kpm-common sc-memory-cpp)
target_link_libraries(sc-kpm-common sc-memory-cpp ${GLIB2_LIBRARIES})
target_compile_definitions(sc-kpm-common PUBLIC "-DSC_KPM_COMMON_SELF_BUILD")
