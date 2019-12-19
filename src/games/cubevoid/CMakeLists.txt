add_executable(CubeVoid main.cpp)

target_link_libraries(CubeVoid 
    Core 
    Render 
    Simulation
)
target_include_directories(CubeVoid PRIVATE ../..)
target_compile_features(CubeVoid PRIVATE cxx_std_17)