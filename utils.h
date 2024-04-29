#pragma once
#include <iostream>
#include <fstream>
#include <stdarg.h>

using namespace std;

//
namespace file_io
{
	//
	void write_to_file(const char* filename, unsigned int argc, ...);
	
	//
	void write_to_file_2(const char* filename, unsigned int argc, ...);

	//
	void readTmplFile(const char* filename);

	//
	void wtof_(const char* filename, const char* c_author, const char* c_content);

	//
	void wtof_2(const char* filename, const char* c_first_name, const char* c_last_name,
		const char* c_gender, const char* c_work_place, const char* c_age, const char* c_income, const char * c_purpose);
}
