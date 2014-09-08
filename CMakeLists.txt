cmake_minimum_required(VERSION 2.8.4)
project(os-cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_custom_target(
    src
    WORKING_DIRECTORY ~/Projects/os/src/
    COMMAND make
    VERBATIM
)

add_custom_target(
    clean
    WORKING_DIRECTORY ~/Projects/os/src/
    COMMAND make clean
    VERBATIM
)