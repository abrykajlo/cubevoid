/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include "log.h"

#include <cstdio>


Log::Log(const char * fileName)
{
	file_.Open(fileName);
}

Log::~Log()
{
	file_.Flush();
}

int Log::Write(const char* line)
{
	return file_.Write(line);
}
