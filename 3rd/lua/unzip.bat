7z x -y .\lua-5.3.4.tar.gz
7z x -y .\lua-5.3.4.tar

if not exist "..\..\include\lua\" (
	mkdir ..\..\include\lua
)
copy .\lua-5.3.4\src\*.h ..\..\include\lua
copy .\lua-5.3.4\src\lua.hpp ..\..\include\lua

if not exist "..\..\src\lua\" (
	mkdir ..\..\src\lua
)
copy .\lua-5.3.4\src\*.c ..\..\src\lua

type nul > .\timestamp.txt