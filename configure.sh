mkdir _builds
cd _builds
conan install ..
cmake -S.. -G"Unix Makefiles"