echo 7z x -y .\glew-2.0.0.zip
7z x -y .\glew-2.0.0.zip

if not exist "..\..\include\GL\" (
	mkdir ..\..\include\GL
)
copy .\glew-2.0.0\include\GL\*.* ..\..\include\GL\

copy .\glew-2.0.0\src\*.* ..\..\src\