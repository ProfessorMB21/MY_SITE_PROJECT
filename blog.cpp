#include "cgi.h"
#include "utils.h"

using namespace cgi_utils;
using namespace file_io;

void form_data()
{
	cout << "<form action=\"blog\" method=\"post\" class=\"comment-form\">";
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
	cout << "<textarea name=\"user-comment\" id=\"comment\" rows=\"2\" cols=\"250\" placeholder=\"Comment here...\" minlength=\"4\" maxlength=\"4086\" required=\"required\"></textarea>";
	cout << "</div>";
	cout << "<input name=\"submit\" type=\"submit\" value=\"Submit comment\"/>";
	cout << "</form>";

	// To check that to server was sended post request use this
	if (get_request_method() == post) {
		// Logic of using get_param_value use here
		char* data = nullptr;

		get_form_data(data);

		cout << "<br>Your details: " << data << endl;
		char* user_name = nullptr;
		char* user_comment = nullptr;
		char* email = nullptr;
		const char* filename = "blog_data.txt";

		get_param_value(data, "user-name", user_name);
		get_param_value(data, "user-comment", user_comment);
		get_param_value(data, "user-email", email);

		// log data to file
		write_to_file(filename, 1, user_name);
		write_to_file(filename, 1, email);
		write_to_file(filename, 1, user_comment);
	}
	
}

void make_comment()
{
	char* author_name = nullptr;
	char* author_comment = nullptr;

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



void blog_page()
{
	const char* filename = "E:/Games/OSPanel/domains/localhost/blog.tmpl";
	ifstream file(filename);
	if (file.is_open())
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			// U haved a bug here: u used `strcmp` not `!strcmp`
			
			if (!strcmp(line, "<!--SOURCE-->")) {
				form_data();
			}
			//if (!strcmp(line, "<!--ENTRY-->")) make_comment();
			else if (!strcmp(line, "<!--CONTENT-->"))
			{
				cout << "Thank you for commenting!\n";
			}
			else {
				cout << line << endl;
			}
		}
		file.close();
		delete[] line;
	}
}
