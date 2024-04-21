// The blog page of my_site.com

#include "cgi.h"
#include "utils.h"

using namespace cgi_utils;
using namespace file_io;

void form_data();
void make_comment();

struct blog_dump
{
	char* m_usrname = nullptr;
	char* m_usr_comment = nullptr;

	void print()
	{
		cout << "Dump: " << m_usrname << "\n" << m_usr_comment << endl;
	}
};

// struct to repr the blog node
struct blog_node_t
{
	char* m_username = nullptr;
	char* m_user_comment = nullptr;
	blog_node_t* next = nullptr;

public:
	blog_node_t() {}

	blog_node_t(char* _username, char* _user_comment)
		: m_username(_username), m_user_comment(_user_comment)
	{}

};

//// struct to repr the blog struct
struct blog_stack_t
{
	blog_node_t* top;
	
private:
	static inline void pretty(char* __name, char* __comment)
	{
		cout << "<div id=\"comment-block\">";
		cout << "<div id=\"author-thumbnail\">";
		cout << "<a href =\"#\">";
		cout << "<div id=\"author-thumbnail-circle\"></div></a></div>";
		cout << "<div id=\"main\">";
		cout << "<div id=\"comment-header\">";
		cout << "<p>@" << __name << "</p>";
		cout << "</div>";
		cout << "<div id=\"comment-content\">";
		cout << "<p>" << __comment << "</p></div>";
		cout << "<div id=\"comment-action-buttons\"></div>";
		cout << "</div></div>\n";
	}

public:
	blog_stack_t ()
	{
		top = nullptr;
	}

	void push(char* _username, char* _comment)
	{
		blog_node_t* new_node = new blog_node_t(_username, _comment);
		new_node->next = top;
		top = new_node;
	}

	void push(blog_node_t& _node)
	{
		blog_node_t* new_node = new blog_node_t;
		new_node->m_username = _node.m_username;
		new_node->m_user_comment = _node.m_user_comment;
		new_node->next = top;
		top = new_node;
	}

	bool pop(blog_dump& dump)
	{
		if (top)
		{
			dump.m_usrname = top->m_username;
			dump.m_usr_comment = top->m_user_comment;
			auto* temp = top;
			delete temp;
			top = top->next;
			return true;
		}
		return false;
	}

	bool pop()
	{
		if (top)
		{
			auto* temp = top;
			delete temp;
			top = top->next;
			return true;
		}
		return false;
	}

	bool peek(blog_dump& dump)
	{
		if (top)
		{
			dump.m_usrname = top->m_username;
			dump.m_usr_comment = top->m_user_comment;
			return true;
		}
		return false;
	}

	void clear()
	{
		while (top)
		{
			auto* temp = top;
			top = top->next;
			delete temp;
		}
	}

	void print()
	{
		while (top)
		{
			auto* temp = top;
			pretty(temp->m_username, temp->m_user_comment);
			top = top->next;
		}
		cout << "Stack length: " << len() << endl;
	}

	int len()
	{
		int _len = 0;
		while (top)
		{
			top = top->next;
			_len++;
		}
		return _len;
	}

};

void _make_comment()
{
	blog_stack_t stack;

	ifstream file("blog_stacking.txt");
	if (file)
	{
		char* name = new char;
		char* comment = new char;

		char* line1 = new char[100000];
		char* line2 = new char[100000];
		while (!file.eof())
		{
			file.getline(line1, 100000);
			file.getline(line2, 100000);
			if (line1 && line2) // read first line
			{
				cout << "line1: " << line1 << "\n" << "line2: " << line2 << endl;
				strcpy_s(name, strlen(line1) + 1, line1);
				strcpy_s(comment, strlen(line2) + 1, line2);
				stack.push(name, comment);
			}
		}
		delete name; delete comment;
		file.close();
	}
	// print stack after file processing
	stack.print();
}

// Program entry point
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
				//make_comment();
				_make_comment(); // prototype
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
	cout << "<input name=\"submit\" type=\"submit\" value=\"Submit comment\"/>";
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
			write_to_file_2("blog_stacking.txt", 2, user_name, user_comment);
		}
		delete[] data;
	}
}
