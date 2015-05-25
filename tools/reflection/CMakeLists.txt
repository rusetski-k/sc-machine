set (SC_BUILDER_DIR "${SC_TOOLS_DIR}/reflection")

set (SOURCES 
    "sc_reflection.cpp"
    "sc_refl_generator.cpp"

    "sc_refl_generator.hpp"
    "sc_refl_types.hpp"
    )

# find dependencies
find_package(LibClang REQUIRED)

include_directories(${LIBCLANG_INCLUDE_DIRS})

add_executable(sc-reflection ${SOURCES})
target_link_libraries(sc-reflection boost_filesystem boost_program_options boost_system ${LIBCLANG_LIBRARIES} )

