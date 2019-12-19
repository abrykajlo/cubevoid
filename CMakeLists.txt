cmake_minimum_required(VERSION 3.14)
project(CubeVoid)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(src/core)
add_subdirectory(src/render)
add_subdirectory(src/simulation)

add_subdirectory(src/games/cubevoid)