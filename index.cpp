#include "main.h"

void main_page();

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("index.tmpl");
	if (file.is_open())
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			if (strcmp(line, "<!--CONTENT-->"))
			{

				if (strcmp(q_string, "blog.html")) blog_page();
				else if (strcmp(q_string, "table.html")) stats_page();
				else if (strcmp(q_string, "about.html")) info_page();
				else main_page();
			}
			else
				cout << line << endl;
		}
		delete[] line; file.close();
	}
	return 0;
}

/*/
void showContent()
{
	if (q_string)
	{
		if (strcmp(q_string, "blog.html")) blog_page();
		else if (strcmp(q_string, "table.html")) stats_page();
		else if (strcmp(q_string, "about.html")) info_page();
		else main_page();
	}
}
*/


void main_page()
{
	cout << "<div class='div-form'>";
	cout << "<p>Fill in the form</p>";
	cout << "<form method='post' action='index.cgi' class='login-form'>\n";
	cout << "<input type=\"text\" name='first-name' placeholder=\"First name\" required>";
	cout << "<input type=\"text\" name='last-name' placeholder=\"Last name\" required>";
	cout << "<input type=\"email\" name='email' placeholder=\"Email\" required>";
	cout << "<input type=\"password\" name='passw' placeholder=\"Password\" required>";
	cout << "<input type=\"submit\" value=\"Sign In\">" << endl;
	char* data = nullptr;

#ifndef _DEBUG
	cout << "<br>Method: " << (get_req_method() == post ? "POST" : "GET");
	get_form_data(data);
#else
	data = _strdup("first-name=%D1%E5%F0%E3%E5%E9&last-name=%D1%E5%F0%E3%E5%E9&email=%D1%E5%F0%E3%E5%E9");
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
	write_to_file(first_name, filename);
	write_to_file(last_name, filename);
	write_to_file(email, filename);
	write_to_file(password, filename);

	delete[] data;
}
