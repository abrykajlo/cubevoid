echo 7z x -y .\SDL2-devel-2.0.5-VC.zip
7z x -y .\SDL2-devel-2.0.5-VC.zip

if not exist "..\..\..\lib\" (
	mkdir ..\..\..\lib\
)
copy .\SDL2-2.0.5\lib\x64\SDL2.lib ..\..\..\lib\
copy .\SDL2-2.0.5\lib\x64\SDL2main.lib ..\..\..\lib\

if not exist "..\..\..\include\SDL2\" (
	mkdir ..\..\..\include\SDL2
)
copy .\SDL2-2.0.5\include\*.* ..\..\..\include\SDL2\

if not exist "..\..\..\install\" (
	mkdir ..\..\..\install\
)
copy .\SDL2-2.0.5\lib\x64\SDL2.dll ..\..\..\install\

type nul > timestamp.txt