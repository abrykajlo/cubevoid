add_library(Render)
target_include_directories(Render PRIVATE .. /usr/include)
target_sources(Render
    PRIVATE
        camera.cpp
        mesh.cpp
        render.cpp
        shader_program.cpp
        shader.cpp
)