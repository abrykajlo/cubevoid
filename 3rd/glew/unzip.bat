echo 7z x -y .\glew-2.0.0-win32.zip
7z x -y .\glew-2.0.0-win32.zip

if not exist "..\..\lib\" (
	mkdir ..\..\lib\
)
copy .\glew-2.0.0\lib\Release\x64\glew32s.lib ..\..\lib\

if not exist "..\..\include\GL\" (
	mkdir ..\..\include\GL
)
copy .\glew-2.0.0\include\GL\*.* ..\..\include\GL\