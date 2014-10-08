cmake_minimum_required(VERSION 2.8.4)
project(os-cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_DIR ~/Projects/os/src)

file(GLOB_RECURSE CPPFILES src/kernel/*.cpp src/modules/*.cpp src/user/*.cpp)
file(GLOB_RECURSE CFILES src/kernel/*.c src/modules/*.c src/user/*.c)
file(GLOB_RECURSE SFILES src/kernel/*.s src/modules/*.s src/user/*.s)
file(GLOB_RECURSE IFILES src/include/*)

file(GLOB_RECURSE KSRC src/kernel/*.cpp src/kernel/*.c src/kernel/*.s)
file(GLOB_RECURSE KHDR src/kernel/*.hpp src/kernel/*.h)

file(GLOB_RECURSE MSRC src/modules/*.cpp src/modules/*.c src/modules/*.s)
file(GLOB_RECURSE MHDR src/modules/*.hpp src/modules/*.h)

file(GLOB_RECURSE USRC src/user/*.cpp src/user/*.c src/user/*.s)
file(GLOB_RECURSE UHDR src/user/*.hpp src/user/*.h)

file(GLOB_RECURSE GHDR src/include/*.hpp src/include/*.h)

include_directories(src/include ../cross/i686-pc-btos/include)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_executable(
    dummy_kernel
    ${KSRC} ${GHDR}
)
set_target_properties(dummy_kernel PROPERTIES COMPILE_DEFINITIONS "KERNEL")

add_executable(
	dummy_modules
	${MSRC} ${GHDR}
)
set_target_properties(dummy_modules PROPERTIES COMPILE_DEFINITIONS "KERNEL_MODULE")

add_executable(
	dummy_user
	${USRC} ${GHDR}
)

add_custom_target(
	kernel
	WORKING_DIRECTORY ${PROJECT_DIR}
	COMMAND make kernel
	VERBATIM
	SOURCES ${KSRC}
)
add_dependencies(dummy_kernel kernel)

add_custom_target(
	modules
	WORKING_DIRECTORY ${PROJECT_DIR}
	COMMAND make modules
	VERBATIM
	SOURCES ${MSRC}
)
add_dependencies(dummy_modules modules)

add_custom_target(
	user
	WORKING_DIRECTORY ${PROJECT_DIR}
	COMMAND make user
	VERBATIM
	SOURCES ${USRC}
)
add_dependencies(dummy_user user)

add_custom_target(build)
add_dependencies(build kernel)
add_dependencies(kernel moodules)
add_dependencies(kernel user)

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

add_dependencies(run build)
