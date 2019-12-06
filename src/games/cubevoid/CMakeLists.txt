include_directories(../..)

add_executable(CubeVoid main.cpp)
target_link_libraries(CubeVoid Core Render Simulation)