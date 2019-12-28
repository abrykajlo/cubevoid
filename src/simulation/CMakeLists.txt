add_library(Simulation STATIC simulation.cpp)
target_include_directories(Simulation PRIVATE .. ${GLAD_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})