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
				outfile << "<div id = \"comment-header\">";
				outfile << "<p>" << s << "</p>";
				outfile << "< / div>";
				outfile << "<div id=\"comment-content\">";
				outfile << "<p>This is where the comment lies< / p>";
				outfile << "</div>";
				outfile << "\n";
			}
		}
		// delete[] s;
		outfile.close();
		va_end(pdata);
	}

	// prototype of write_to_file used for comments
	void wtof_(const char* filename, const char * c_author, const char * c_content)
	{
		ofstream outfile(filename, ios_base::app);
		if (!outfile) cerr << "Can't write to file, " << filename;
		if (c_author && c_content)
		{
			outfile << "<div id = \"comment-header\">";
			outfile << "<p>" << c_author << "</p>";
			outfile << "< / div>";
			outfile << "<div id=\"comment-content\">";
			outfile << "<p>" << c_content << "</p>";
			outfile << "</div>";
			outfile << "\n";
		}
		// delete[] s;
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
