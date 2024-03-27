#pragma once

//
namespace cgi_utils
{
	enum request_method {
		get, post
	};

	request_method get_request_method();
	void get_form_data(char*& result);
	void get_param_value(const char* data, const char* param_name, char*& value);
	char* get_current_url();
	char* get_host_ip();
}
