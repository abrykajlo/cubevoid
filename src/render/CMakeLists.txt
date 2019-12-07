add_library(Render)
target_include_directories(Render PRIVATE .. ../3rd)
target_sources(Render
    PRIVATE
        camera.cpp
        mesh.cpp
        render.cpp
        shader_program.cpp
        shader.cpp
)