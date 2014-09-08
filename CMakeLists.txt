cmake_minimum_required(VERSION 2.8.4)
project(os-cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_DIR ~/Projects/os/src/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_DIR})
set(os-cmake_BINARY_DIR ${PROJECT_DIR})

add_custom_target(
    build
    WORKING_DIRECTORY ${PROJECT_DIR}
    COMMAND make
    VERBATIM
)

add_custom_target(
    clean
    WORKING_DIRECTORY ${PROJECT_DIR}
    COMMAND make clean
    VERBATIM
)

add_custom_target(
    run
    WORKING_DIRECTORY ${PROJECT_DIR}
    COMMAND make test
    VERBATIM
)