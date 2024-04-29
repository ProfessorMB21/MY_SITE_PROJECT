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

	enum script_type_err
	{
		no_script_run,
		script_no_data,
		script_err_all,
		script_err_passw,
		script_err_uname,
		script_acc_granted
	};

	script_type_err script_err_run(script_type_err e);
}
