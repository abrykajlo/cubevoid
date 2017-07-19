/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#pragma once

#include <cstdio>

template <typename IoPolicy>
class File
{
public:
	File()
	{}

	File(const char* fileName)
	{
		Open(fileName);
	}

	~File()
	{
		Close();
	}

	int Open(const char* fileName)
	{
		return file_.Open(fileName);
	}

	size_t Size()
	{
		return file_.Size();
	}

	int Read(char* buf, size_t n)
	{
		return file_.Read(buf, n);
	}

	int Write(const char* line)
	{
		return file_.Write(line);
	}

	int Flush()
	{
		return file_.Flush();
	}

	int Close()
	{
		return file_.Close();
	}
private:
	IoPolicy file_;
};

struct DefaultReadPolicy
{
	int Open(const char* fileName)
	{
		auto ret = fopen_s(&file, fileName, "rb");
		if (ret != 0)
		{
			return -1;
		}

		return 0;
	}

	size_t Size()
	{
		fseek(file, 0, SEEK_END);
		auto ret = ftell(file);
		fseek(file, 0, SEEK_SET);
		return ret;
	}

	int Read(char* buf, size_t n)
	{
		return fread(buf, 1, n, file);
	}

	int Close()
	{
		return fclose(file);
	}

	FILE* file;
};

struct DefaultWritePolicy
{
	int Open(const char* fileName)
	{
		auto ret = fopen_s(&file, fileName, "wb");
		if (ret != 0)
		{
			return -1;
		}

		return 0;
	}

	int Write(const char* line)
	{
		return fprintf(file, line);
	}

	int Flush()
	{
		return fflush(file);
	}

	int Close()
	{
		return fclose(file);
	}

	FILE* file;
};

using DefaultWriteFile = File<DefaultWritePolicy>;
using DefaultReadFile = File<DefaultReadPolicy>;