add_library(Render STATIC)
target_include_directories(Render PRIVATE .. /usr/include)
target_sources(Render
    PUBLIC
        camera.cpp
        mesh.cpp
        render.cpp
        shader_program.cpp
        shader.cpp
)