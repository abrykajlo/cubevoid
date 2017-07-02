7z x -y .\SDL2-devel-2.0.5-VC.zip

if not exist ".\lib\" (
	mkdir .\lib\
)
copy .\SDL2-2.0.5\lib\x64\SDL2.lib .\lib\
copy .\SDL2-2.0.5\lib\x64\SDL2main.lib .\lib\

if not exist ".\SDL2\" (
	mkdir .\SDL2
)
copy .\SDL2-2.0.5\include\*.* .\SDL2\
copy .\SDL2-2.0.5\lib\x64\SDL2.dll ..\..\..\install\

type nul > timestamp.txt