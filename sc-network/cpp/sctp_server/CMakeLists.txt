
set (SOURCES
    "main.cpp"
    "sctpClient.cpp"
    "sctpCommand.cpp"
    "sctpServer.cpp"
    "sctpStatistic.cpp"
    "sctpEventManager.cpp"
    )

set (HEADERS
    "sctpClient.h"
    "sctpCommand.h"
    "sctpServer.h"
    "sctpStatistic.h"
    "sctpEventManager.h"
    "sctpTypes.h"
    )


# based on http://qt-project.org/doc/qt-5/cmake-manual.html

# Find the QtWidgets library
find_package(Qt5Network)
find_package(Qt5Core)
# Use the compile definitions defined in the Qt 5 module
add_definitions(${Qt5Core_DEFINITIONS} ${Qt5Network_DEFINITIONS})
# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


add_executable(sctp-server ${SOURCES} ${HEADERS} ${HEADERS_MOC})
include_directories(${SC_MEMORY_SRC} ${GLIB2_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})
target_link_libraries(sctp-server sc-memory Qt5::Core Qt5::Network)

install_targets("/bin" sctp-server)
