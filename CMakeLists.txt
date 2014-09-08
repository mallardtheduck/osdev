cmake_minimum_required(VERSION 2.8.4)
project(os-cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_DIR ~/Projects/os/src)

file(GLOB_RECURSE CPPFILES src/kernel/*.cpp src/modules/*.cpp src/user/*.cpp)
file(GLOB_RECURSE CFILES src/kernel/*.c src/modules/*.c src/user/*.c)
file(GLOB_RECURSE SFILES src/kernel/*.s src/modules/*.s src/user/*.s)
file(GLOB_RECURSE IFILES src/include/*)

set(SRCFILES ${CPPFILES} ${CFILES} ${SFILES} ${IFILES})

add_executable(
    dummy
    ${SRCFILES}
)

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