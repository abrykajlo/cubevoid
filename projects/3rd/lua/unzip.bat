7z x -y .\lua-5.3.4.tar.gz
7z x -y .\lua-5.3.4.tar

if not exist ".\lua\" (
	mkdir .\lua
)
copy .\lua-5.3.4\src\*.h .\lua
copy .\lua-5.3.4\src\lua.hpp .\lua
copy .\lua-5.3.4\src\*.c .\lua

type nul > .\timestamp.txt