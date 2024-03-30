#include "utils.h"

//
namespace file_io
{
	// Function write data from forms to a specified file
	void write_to_file(const char* filename, unsigned int argc, ...)
	{
		va_list pdata;
		char* s = nullptr;

		va_start(pdata, argc);

		ofstream outfile(filename, ios_base::app);
		if (!outfile) cerr << "Can't write to file, " << filename;

		for (unsigned int i = 0; i < argc; i++)
		{
			s = va_arg(pdata, char*);
			if (s)
			{
				outfile.write(s, strlen(s) + 1);
				outfile << "\n";
			}
		}
		// delete[] s;
		outfile.close();
		va_end(pdata);
	}

	// Function write data from forms to a specified file
	// second variant of write_to_file function specifically for queue task requirement
	// Args must be in the following order;
	//		- Full name (first name and last name as separate args)
	//		- Gender
	//		- Age
	//		- Place of work
	//		- Income
	//		- Purpose of application
	//
	void write_to_file_2(const char* filename, unsigned int argc, ...)
	{
		va_list pdata;
		char* s = nullptr;

		va_start(pdata, argc);

		ofstream outfile(filename, ios_base::app);
		if (outfile.is_open())
		{
			for (unsigned int i = 0; i < argc; i++)
			{
				s = va_arg(pdata, char*);
				outfile << s << "|";
			}
			outfile << '\n';
			outfile.close();
		}
		va_end(pdata);
	}

	// prototype of write_to_file used for comments
	void wtof_(const char* filename, const char * c_author, const char * c_content)
	{
		ofstream outfile(filename, ios_base::app);
		if (outfile)
		{
			outfile << "<div id=\"comment-block\">";
			outfile << "<div id=\"author-thumbnail\">";
			outfile << "<a href =\"#\">";
			outfile << "<div id=\"author-thumbnail-circle\"></div></a></div>";
			outfile << "<div id=\"main\">";
			outfile << "<div id=\"comment-header\">";
			outfile << "<p>@" << c_author << "</p>";
			outfile << "</div>";
			outfile << "<div id=\"comment-content\">";
			outfile << "<p>" << c_content << "</p></div>";
			outfile << "<div id=\"comment-action-buttons\"></div>";
			outfile << "</div></div>";
			outfile << '\n';
		}
		outfile.close();
	}

	// prototype of write_to_file used for table items on client page
	void wtof_2(const char* filename, const char* c_first_name, const char* c_last_name,
		const char* c_gender, const char* c_work_place, const char* c_age, const char* c_income, const char * c_purpose)
	{
		ofstream outfile(filename, ios_base::app);
		if (outfile)
		{
			outfile << "<div class=\"row\">";
			outfile << "<div class=\"cell\" data-title=\"Full Name\">";
			outfile << c_first_name << " " << c_last_name << "</div>";
			outfile << "<div class=\"cell\" data-title=\"Sex\">";
			outfile << c_gender << "</div>";
			outfile << "<div class=\"cell\" data-title=\"Age\">";
			outfile << c_age << "</div>";
			outfile << "<div class=\"cell\" data-title=\"Location\">";
			outfile << c_work_place << "</div></div>";
			outfile << "<div class=\"cell\" data-title=\"Salary\">";
			outfile << c_income << "</div>";
			outfile << "<div class=\"cell\" data-title=\"Job Title\">";
			outfile << c_purpose << "</div>";
			outfile << '\n';
		}
		outfile.close();
	}


	// This function is just for reading static tmpl files.
	void readTmplFile(const char* filename) {
		ifstream file(filename);

		if (file.is_open()) {
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
}
