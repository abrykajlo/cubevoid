add_executable(CubeVoid main.cpp)

target_link_libraries(CubeVoid 
    Core 
    Render 
    Simulation
    OpenGL::GL
    glad
    glfw
)
target_include_directories(CubeVoid PRIVATE ../..)
target_compile_features(CubeVoid PUBLIC cxx_std_17)
add_custom_command(TARGET CubeVoid PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/src/games/cubevoid/install $<TARGET_FILE_DIR:CubeVoid>)