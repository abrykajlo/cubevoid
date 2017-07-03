#pragma once

#include <cstdio>

class Log
{
public:
	Log(const char* filename);
	~Log();

	int Write(const char* line);
private:
	FILE* file_;
};