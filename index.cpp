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
			cout << "<input type=\"text\" name='user-name' placeholder=\"Username\" required>";
			//cout << "<input type=\"email\" name='email' placeholder=\"Email\" required>";
			cout << "<input type=\"password\" name='passw' placeholder=\"Password\">";
			cout << "<input type=\"submit\" id='btn-submit' value=\"Sign In\"></form>" << endl;

			if (get_request_method() == post)
			{
				char* data = nullptr;
				script_type_err error_code = no_script_run; // to manage incorrect client input

				get_form_data(data);

				const char* tmp_pwd = "me";
				const char* tmp_uname = "bupe";


				char* username = nullptr;
				char* password = nullptr;
				const char* filename = "data.txt";

				get_param_value(data, "user-name", username);
				get_param_value(data, "passw", password);
				if (!strcmp(password, tmp_pwd) && !strcmp(username, tmp_uname))
				{
					error_code = script_acc_granted;
					script_err_run(error_code);
					cout << "<meta http-equiv='refresh' content='0;URL=blog.cgi'>\n";
				}
				else if (strcmp(username, tmp_uname) && strcmp(password, tmp_pwd)) // check if both the password and username are incorrect
				{
					error_code = script_err_all;
					script_err_run(error_code);
				}
				else if (strcmp(username, tmp_uname))
				{
					error_code = script_err_uname;
					script_err_run(error_code);
				}
				else if (strcmp(password, tmp_pwd))
				{
					error_code = script_err_passw;
					script_err_run(error_code);
				}
				cout << "</div>" << endl;

				// log all data to a file before cleaning
				write_to_file_2(filename, 2, username, password);
				delete[] data;
			}
		}
		else
			cout << line << endl;
	}
	delete[] line;
	file.close();
	return 0;
}
