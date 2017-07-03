/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


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
