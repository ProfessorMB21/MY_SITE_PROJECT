#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

enum request_method
{
	get = 1,
	post
};

request_method get_req_method();
void get_form_data(char*& result);
void get_param_value(const char* data, const char* param_name, char*& value);
void write_to_file(const char* data, const char * filename);

void showContent(const char* q_string);

int info_page();
int stats_page();
int blog_page();

#endif // !MAIN_H
