
add_library(sc-kpm-core SHARED
    "sc_kpm.cpp"
    "sc_kpm_agent.cpp"
    "sc_kpm_module.cpp"
    "sc_kpm_keynodes.cpp"

    "sc_kpm_prerequest.hpp"
    "sc_kpm_defines.hpp"

    "sc_kpm.hpp"
    "sc_kpm_agent.hpp"
    "sc_kpm_module.hpp"
    "sc_kpm_keynodes.hpp"
    "sc_kpm_headers.hpp"
    )

include_directories(${SC_MACHINE_ROOT})
add_dependencies(sc-kpm-core sc-memory-cpp)
target_link_libraries(sc-kpm-core sc-memory-cpp)

