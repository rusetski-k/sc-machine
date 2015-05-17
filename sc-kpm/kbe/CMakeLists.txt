
add_library(sc-kpm-kbe SHARED
            "sc_kpm_kbe.cpp"

            "sc_kpm_kbe.hpp"
            )

include_directories(${SC_MACHINE_ROOT})
add_dependencies(sc-kpm-kbe sc-kpm-core)
target_link_libraries(sc-kpm-kbe sc-kpm-core)

