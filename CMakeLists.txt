cmake_minimum_required(VERSION 3.14)

project(CubeVoid)

add_subdirectory(src/core)
add_subdirectory(src/render)
add_subdirectory(src/simulation)
add_subdirectory(src/3rd)

add_subdirectory(src/games/cubevoid)
target_include_directories(CubeVoid PUBLIC src)