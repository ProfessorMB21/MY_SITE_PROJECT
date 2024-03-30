// The blog page of my_site.com

#include "cgi.h"
#include "utils.h"

using namespace cgi_utils;
using namespace file_io;

void form_data();
void make_comment();

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("blog.tmpl");
	if (file.is_open())
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			if (!strcmp(line, "<!--FORM-->"))
			{
				form_data();
			}
			if (!strcmp(line, "<!--SOURCE-->"))
			{
				make_comment();
			}
			else
				cout << line << endl;
		}
		file.close();
		delete[] line;
	}
	return 0;
}

void make_comment()
{
	ifstream file("blog_data.txt");
	if (file.is_open())
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			cout << line << endl;
		}
		delete[] line;
		file.close();
	}
}

void form_data()
{
	cout << "<form action=\"blog.cgi\" method=\"post\" class=\"comment-form\">";
	cout << "<div>";
	cout << "<label for=\"comment_author\" class=\"required\">Your name</label>";
	cout << "<input name=\"user-name\" type=\"text\" placeholder =\"Full name\" required=\"required\">";
	cout << "</div>";

	// under development
	/*
	cout << "<div>";
	cout << "<label for=\"email\" class=\"required\">Your email< / label>";
	cout << "<input name=\"user-email\" type=\"email\" placeholder=\"user@domain.com\" required=\"required\">";
	cout << "</div>";
	*/
	cout << "<div>";
	cout << "<label for=\"comment\" class=\"required\">Your message</label>";
	cout << "<textarea name=\"user-comment\" id=\"comment\" rows=\"2\" cols=\"1500\" placeholder=\"Comment here...\" minlength=\"4\" maxlength=\"4086\" required=\"required\"></textarea>";
	cout << "</div>";
	cout << "<input name=\"submit\" type=\"submit\" id='btn-submit' value=\"Submit comment\"/>";
	cout << "</form>";

	if (get_request_method() == post) {
		char* data = nullptr;

		get_form_data(data);

		char* user_name = nullptr;
		char* user_comment = nullptr;
		const char* filename = "blog_data.txt";

		get_param_value(data, "user-name", user_name);
		get_param_value(data, "user-comment", user_comment);
		if (user_name && user_comment)
		{
			wtof_(filename, user_name, user_comment);
		}
	}
}
