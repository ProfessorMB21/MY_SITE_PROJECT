// The homepage of my_site.com

#include "cgi.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace cgi_utils;
using namespace file_io;

int main(){
	setlocale(LC_ALL, "rus");
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	char* current_url = get_current_url();

	ifstream file("index.tmpl");
	if (!file.is_open()) return -1;

	char* line = new char[1024];
	while (!file.eof())
	{
		file.getline(line, 1024);
		if (!strcmp(line, "<!--CONTENT-->"))
		{
			cout << "<div class='div-form'>";
			cout << "<p>Fill in the form</p>";
			cout << "<form method='post' action='index.cgi' class='login-form'>\n";
			cout << "<input type=\"text\" name='first-name' placeholder=\"First name\" required>";
			cout << "<input type=\"text\" name='last-name' placeholder=\"Last name\" required>";
			cout << "<input type=\"email\" name='email' placeholder=\"Email\" required>";
			cout << "<input type=\"password\" name='passw' placeholder=\"Password\">";
			cout << "<input type=\"submit\" id='btn-submit' value=\"Sign In\">" << endl;

			char* data = nullptr;

#ifndef _DEBUG
			get_form_data(data);
#else
			data = _strdup("username=%D1%E5%F0%E3%E5%E9&age=43");
#endif
			char* first_name = nullptr;
			char* last_name = nullptr;
			char* password = nullptr;
			char* email = nullptr;
			const char* filename = "data.txt";

			get_param_value(data, "first-name", first_name);
			get_param_value(data, "last-name", last_name);
			if (first_name && last_name)
				cout << "<p>Welcome, " << first_name << " " << last_name << "</p>";

			get_param_value(data, "passw", password);
			if (password)
			{
				cout << "Your password: " << password << "<br>\n";
				cout << "Your IP address: <p>" << get_host_ip() <<"</p>\n";
			}
			cout << "</div>" << endl;

			// log all data to a file before cleaning
			write_to_file(filename, 3, first_name, last_name, password);

			delete[] data;
		}
		else
			cout << line << endl;
	}
	delete[] line;
	file.close();
	return 0;
}
