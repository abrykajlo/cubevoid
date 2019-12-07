add_library(Simulation simulation.cpp)
target_include_directories(Simulation PRIVATE .. ../3rd)
target_link_libraries(Simulation
    PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/SDL2.lib 
)