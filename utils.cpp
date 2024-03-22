#include "utils.h"

//
namespace file_io
{
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
				outfile.write(s, sizeof(s));
				outfile << "\n";
			}
		}
		// delete[] s;
		outfile.close();
		va_end(pdata);
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
