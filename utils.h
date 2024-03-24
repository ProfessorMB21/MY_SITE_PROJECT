#pragma once
#include <iostream>
#include <fstream>
#include <stdarg.h>

using namespace std;

//
namespace file_io
{
	void write_to_file(const char* filename, unsigned int argc, ...);
	void readTmplFile(const char* filename);
	void wtof_(const char* filename, const char* c_author, const char* c_content);
}
