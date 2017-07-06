7z x -y .\glew-2.0.0.zip

if not exist ".\GL\" (
	mkdir .\GL
)
copy .\glew-2.0.0\include\GL\glew.h .\GL\
copy .\glew-2.0.0\include\GL\wglew.h .\GL\

copy .\glew-2.0.0\src\glew.c .\glew.c

type nul > .\timestamp.txt