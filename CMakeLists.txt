cmake_minimum_required(VERSION 3.16)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c libs/data_structures/matrix/matrix.c libs/data_structures/matrix/matrix.h libs/algoritms/array/array.c libs/algoritms/array/array.h)

add_subdirectory(libs)
target_link_libraries(untitled data_structures)
target_link_libraries(untitled algoritms)