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

	// Trying to save from spaghetti code.
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
			cout << "<input type=\"submit\" value=\"Sign In\">" << endl;

			char* data = nullptr;
			//get_form_data(data);
			char* value = nullptr;

#ifndef _DEBUG
			cout << "<br>Method: " << (get_request_method() == post ? "POST" : "GET");
			get_form_data(data);
#else
			data = _strdup("username=%D1%E5%F0%E3%E5%E9&age=43");
#endif
			cout << "<br>Your details: " << data << endl;
			char* first_name = nullptr;
			char* last_name = nullptr;
			char* password = nullptr;
			char* email = nullptr;
			const char* filename = "data.txt";

			get_param_value(data, "first-name", first_name);
			get_param_value(data, "last-name", last_name);
			get_param_value(data, "passw", password);
			get_param_value(data, "email", email);
			if (first_name && last_name)
				cout << "<p>Welcome, " << first_name << " " << last_name << "</p>";
			if (password)
				cout << "Your password: " << password;
			cout << "</div>" << endl;

			// log all data to a file before cleaning
			write_to_file(filename, 2, first_name, last_name);
			//write_to_file(filename, last_name);
			write_to_file(filename, 1, email);
			write_to_file(filename, 1, password);

			delete[] data;
		}
		else
			cout << line << endl;
	}
	delete[] line;
	file.close();
	return 0;
}
