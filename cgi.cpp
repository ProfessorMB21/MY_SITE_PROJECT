#include "cgi.h"
#include <iostream>
using namespace std;

//
namespace cgi_utils
{
	request_method get_request_method() {
		size_t realsize;
		size_t sz = 5;
		char* buf = new char[sz];
		getenv_s(&realsize, buf, sz, "REQUEST_METHOD");
		request_method result;
		if (_strcmpi(buf, "post")) result = request_method::get;
		else result = request_method::post;
		delete[] buf;
		return result;
	}

	size_t get_content_length() {
		size_t realsize;
		size_t sz = 11;
		char* buf = new char[sz];
		getenv_s(&realsize, buf, sz, "CONTENT_LENGTH");
		sscanf_s(buf, "%llu", &realsize);
		delete[] buf;
		return realsize;
	}

	char* get_current_url() {
		size_t realsize;
		size_t sz = 65536;
		char* buf = new char[sz];
		getenv_s(&realsize, buf, sz, "PATH_INFO");
		return buf;
	}

	void get_form_data(char*& result) {
		delete[] result;
		if (get_request_method() == request_method::get) {
			size_t realsize;
			size_t sz = 65536;
			char* buf = new char[sz];
			getenv_s(&realsize, buf, sz, "QUERY_STRING");
			result = new char[realsize + 1];
			strcpy_s(result, realsize + 1, buf);
			delete[] buf;
		}
		else {
			auto sz = get_content_length();
			result = new char[sz + 1];

			fread_s(result, sz + 1, sizeof(char), sz + 1, stdin);
			result[sz] = 0;
		}
	}

	void decode(const char* encoded_str, char*& decoded_str) {
		delete[] decoded_str;
		decoded_str = nullptr;
		char* tmp = new char[strlen(encoded_str) + 1];
		char* symb = (char*)encoded_str;
		int i = 0;
		while (*symb) {
			if (*symb == '+') tmp[i] = ' ';
			else if (*symb == '%') {
				char* s = new char[3];
				s[0] = *(++symb);
				s[1] = *(++symb);
				s[2] = 0;
				int c;
				sscanf_s(s, "%x", &c);
				delete[] s;
				tmp[i] = c;
			}
			else {
				tmp[i] = *symb;
			}
			i++;
			symb++;
		}
		tmp[i] = 0;
		decoded_str = new char[strlen(tmp) + 1];
		strcpy_s(decoded_str, strlen(tmp) + 1, tmp);
		delete[] tmp;
	}

	void get_param_value(const char* data, const char* param_name, char*& value) {
		delete[] value;
		value = nullptr;
		char* tmp = _strdup(data);
		char* cntx = nullptr;
		while (char* kv = strtok_s(tmp, "&", &cntx)) {
			tmp = nullptr;
			char* v = nullptr;
			char* key = strtok_s(kv, "=", &v);
			if (_strcmpi(param_name, key) == 0) {
				if (v != nullptr) {
					decode(v, value);
				}

				break;
			}

		}
	}

	// Returns the host's remote IP address
	char* get_host_ip()
	{
		size_t realsize;
		size_t size = 65536;
		char* buf = new char[size];
		getenv_s(&realsize, buf, size, "REMOTE_ADDR");
		char* addr = new char[realsize + 1];
		strcpy_s(addr, realsize + 1, buf);
		delete[] buf;
		return addr;
	}
}
