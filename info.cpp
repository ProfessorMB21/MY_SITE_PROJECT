#include "main.h"

int info_page()
{
	cout << "Content-type: text/html; charset=windows-1251\n\n";

	ifstream file("about.tmpl");
	if (file.is_open())
	{

	}

	return 0;
}
