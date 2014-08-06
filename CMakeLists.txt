cmake_minimum_required(VERSION 2.8)
project(legitJIT)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Werror")
SET(GCC_COVERAGE_LINK_FLAGS    "")



SET(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file(GLOB_RECURSE PROJECT_SOURCES "src/lib/*.c")
file(GLOB_RECURSE PROJECT_HEADERS "src/lib/*.h")

set (PROJECT_INCLUDE_DIRS "")
foreach (_headerFile ${PROJECT_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PROJECT_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES PROJECT_SOURCE_DIR)

include_directories(${PROJECT_INCLUDE_DIRS})

add_library(legitJITLib STATIC ${PROJECT_SOURCES})

add_executable(legitJIT src/main.c)

TARGET_LINK_LIBRARIES(legitJIT legitJITLib)
