#include "main.h"

/*
void read_from_html(const char* src, const char* dest, const char* limit)
{
	cout << "Content-type: text/html; charset=windows-1251\n\n";
	
	ofstream dest_file(dest);
	ifstream src_file(src);
	if (!dest_file || !src_file) return;

	char* buf = new char[1024];

	while (!src_file.eof())
	{
		src_file.getline(buf, 1024);
		if (!strcmp(buf, limit))
		{
			cout << 
		}
	}
}
*/

request_method get_req_method()
{
	size_t realsize;
	size_t size = 5;
	char* buf = new char[5];
	getenv_s(&realsize, buf, size, "REQUEST_METHOD");
	request_method result;
	if (_strcmpi(buf, "post")) result = request_method::get;
	else result = request_method::post;
	delete[] buf;
	return result;
}

size_t get_content_len()
{
	size_t realsize;
	size_t size = 11;
	char* buf = new char[size];
	getenv_s(&realsize, buf, size, "CONTENT_LENGTH");
	sscanf_s(buf, "%llu", &realsize);
	delete[] buf;
	return realsize;
}

void get_form_data(char*& result)
{
	delete[] result;
	if (get_req_method() == request_method::get)
	{
		size_t realsize;
		size_t size = 65536;
		char* buf = new char[size];
		getenv_s(&realsize, buf, size, "QUERY_STRING");
		result = new char[realsize + 1];
		strcpy_s(result, realsize + 1, buf);
		delete[] buf;
	}
	else
	{
		auto size = get_content_len();
		result = new char[size + 1];
		fread_s(result, size + 1, sizeof(char), size + 1, stdin);
	}
}

void decode(const char* encoded_str, char*& decoded_str)
{
	delete[] decoded_str;
	decoded_str = nullptr;
	char* temp = new char[strlen(encoded_str) + 1];
	char* symb = (char*)encoded_str;
	int i = 0;

	while (*symb)
	{
		if (*symb == '+') temp[i] = ' ';
		else if (*symb == '%')
		{
			char* s = new char[3];
			s[0] = *(++symb);
			s[1] = *(++symb);
			s[2] = 0;
			int c;
			sscanf_s(s, "%x", &c);
			delete[] s;
			temp[i] = c;
		}
		else temp[i] = *symb;
		i++;
		symb++;
	}
	temp[i] = 0;
	decoded_str = new char[strlen(temp) + 1];
	strcpy_s(decoded_str, strlen(temp) + 1, temp);
	delete[] temp;
}

void get_param_value(const char* data, const char* param_name, char*& value)
{
	delete[] value;
	value = nullptr;
	char* temp = _strdup(data);
	char* temp2 = temp;
	char* context = nullptr;
	
	while (char* kv = strtok_s(temp, "&", &context))
	{
		temp = nullptr;
		char* v = nullptr;
		char* key = strtok_s(kv, "=", &v);
		if (_strcmpi(param_name, key) == 0)
		{
			if (v != nullptr)
				decode(v, value);
			break;
		}
	}
	delete[] temp2;
}

/*/
void write_to_file(const char* filename, const char* data)
{
	char* cpy = _strdup(data);	// prevent data manipulation 

	ofstream outfile(filename, ios_base::app);
	if (!outfile.is_open())
		cerr << "Can't write to file, " << filename;

	outfile.write(cpy, sizeof(cpy));
	outfile.close();
}
*/

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
