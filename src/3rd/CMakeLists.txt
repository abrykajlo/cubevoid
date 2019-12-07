add_library(3rd)
target_sources(3rd PRIVATE GL/glew.c)
target_include_directories(3rd PUBLIC .)