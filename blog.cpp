#include "main.h"


void make_comment(char* author_name, char* author_comment);
void form_data();

int blog_page()
{
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("blog.tmpl");
	if (file.is_open())
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			if (strcmp(line, "<!--SOURCE-->")) form_data();
			if (strcmp(line, "<!--ENTRY-->")) make_comment();
			if (strcmp(line, "<!--CONTENT-->"))
			{
				cout << "Thank you for commenting!\n";
			}
		} file.close(); delete[] line;
	}
	return 0;
}

void make_comment(char *author_name, char * author_comment)
{
	cout << "<div id=\"comment-block\">";
	cout << "< div id=\"author-thumbnail\">";
	cout << "< a href=\"#\">";
	cout << "<div id=\"author-thumbnail-circle\"> </div>";
	cout << "</a>";
	cout << "</div>";
	cout << "<div id=\"main\">";
	cout << "<div id=\"comment-header\">";
	cout << "<p>@" << author_name << "</p>";
	cout << "</div>";
	cout << "<div id=\"comment-content\">";
	cout << "<p>" << author_comment << "</p>";
	cout << "</div>";
	cout << "</div>";
	cout << "</div>";
	
}

void form_data()
{
	cout << "<form action=\"index.cgi\" method=\"post\" class=\"comment-form\">";
	cout << "<div>";
	cout << "<label for=\"comment_author\" class=\"required\">Your name</label>";
	cout << "<input name=\"user-name\" type=\"text\" placeholder =\"Full name\" required=\"required\">";
	cout << "</div>";
	cout << "<div>";
	cout << "<label for=\"email\" class=\"required\">Your email< / label>";
	cout << "<input name=\"user-email\" type=\"email\" placeholder=\"user@domain.com\" required=\"required\">";
	cout << "</div>";
	cout << "<div>";
	cout << "<label for=\"comment\" class=\"required\">Your message</label>";
	cout << "<textarea name=\"user-comment\" id=\"comment\" rows=\"2\" cols=\"250\" placeholder=\"Comment here...\" minlength=\"8\" maxlength=\"4086\" required=\"required\"></textarea>";
	cout << "</div>";
	cout << "<input name=\"submit\" type=\"submit\" value=\"Submit comment\"/>";
	cout << "</form>";
	char* data = nullptr;

#ifndef _DEBUG
	cout << "<br>Method: " << (get_req_method() == post ? "POST" : "GET");
	get_form_data(data);
#else
	data = _strdup("user-name=%D1%E5%F0%E3%E5%E9&user-email=%D1%E5%F0%E3%E5%E9&user-comment=%D1%E5%F0%E3%E5%E9");
#endif
	cout << "<br>Your details: " << data << endl;
	char* user_name = nullptr;
	char* user_comment = nullptr;
	char* email = nullptr;
	const char* filename = "data.txt";

	get_param_value(data, "user-name", user_name);
	get_param_value(data, "user-comment", user_comment);
	get_param_value(data, "user-email", email);
}
