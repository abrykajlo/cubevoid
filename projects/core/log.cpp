#include <cstdio>

#include "log.hpp"

Log::Log(const char * filename)
{
	fopen_s(&file_, filename, "w");
}

Log::~Log()
{
	fflush(file_);
	fclose(file_);
}

int Log::Write(const char* line)
{
	return fprintf(file_, line);
}
