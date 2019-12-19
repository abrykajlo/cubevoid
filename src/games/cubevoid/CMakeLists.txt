add_executable(CubeVoid main.cpp)

target_link_libraries(CubeVoid 
    Core 
    Render 
    Simulation
    OpenGL::GL
    ${CONAN_LIBS}
)
target_include_directories(CubeVoid PRIVATE ../..)
target_compile_features(CubeVoid PUBLIC cxx_std_17)