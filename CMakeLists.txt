# Top configuration
cmake_minimum_required(VERSION 3.2.2)
project(RType)

# Doxygen
option(BUILD_DOC "Build documentation" OFF)
if(BUILD_DOC EQUAL ON)
    find_package(Doxygen OPTIONAL_COMPONENTS)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started...")

        add_custom_target(Documentation ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating RType documentation with Doxygen"
            VERBATIM)
    else(DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation, continuing")
    endif(DOXYGEN_FOUND)
endif(BUILD_DOC EQUAL ON)

# SFML
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

# Asio (non-boost)
option(ASIO_USE_CPM "Download Asio with CPM instead of FetchContent" OFF)
option(
    ASIO_CPM_FETCHCONTENT_COMPAT
    "Should asio be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
    ON
)
include(FetchContent)
FetchContent_Declare(
    asiocmake
    GIT_REPOSITORY https://github.com/OlivierLDff/asio.cmake.git
    GIT_TAG v1.2.0
)
FetchContent_MakeAvailable(asiocmake)

# Compilation
add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
