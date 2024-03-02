#include "main.h"

int stats_page()
{
    cout << "Content-type: text/html; charset=windows-1251\n\n";
	ifstream file("table.tmpl");
	if (file.is_open())
	{
		char* line = new char[1024];
		while (!file.eof())
		{
			file.getline(line, 1024);
			if (!strcmp(line, "<!--CONTENT-->"))
			{
                cout << "<div>";
                cout << "<table cellspacing=\"0\">";
                cout << "<thead>";
                cout << "<tr>";
                cout << "<th>Discipline</th>";
                cout << "<th>Type</th>";
                cout << "<th>Points earned</th>";
                cout << "</tr>";
                cout << "</thead>";
                cout << "<tbody>";
                cout << "<tr>";
                cout << "<td>Algebra</td>";
                cout << "<td>Exam.</td>";
                cout << "<td>";
                cout << "<p> 79 % </p>";
                cout << "<progress value=\"79\" max=\"100\"></progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "<tr>";
                cout << "<td>Mathematical analysis</td>";
                cout << "<td>Exam.</td>";
                cout << "<td>";
                cout << "<p>83 % </p>";
                cout << "<progress value=\"83\" max=\"100\"></progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "<tr>";
                cout << "<td>Analytical geometry</td>";
                cout << "<td>Test.</td>";
                cout << "<td>";
                cout << "<p>65 % </p>";
                cout << "<progress value=\"65\" max=\"100\"></progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "<tr>";
                cout << "<td>Introduction to the specialization</td>";
                cout << "<td>Test.</td>";
                cout << "<td>";
                cout << "<p>56 % </p>";
                cout << "<progress value=\"56\" max=\"100\"></progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "<tr>";
                cout << "<td>Foreign language: Russian</td>";
                cout << "<td>Test.< / td>";
                cout << "<td>";
                cout << "<p>90 % </p>";
                cout << "<progress value=\"90\" max=\"100\"></progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "<tr>";
                cout << "<td>Russian history</td>";
                cout << "<td>Test.</td>";
                cout << "<td>";
                cout << "<p>78 % </p>";
                cout << "<progress value=\"78\" max=\"100\"></progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "<tr>";
                cout << "<td>Fundamentals of Computer Science</td>";
                cout << "<td>Exam.</td>";
                cout << "<td>";
                cout << "<p>87 % </p>";
                cout << "<progress value=\"87\" max=\"100\"></progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "<tr>";
                cout << "<td>Fundaemntals of Russian Statehood</td>";
                cout << "<td>Test.</td>";
                cout << "<td>";
                cout << "<p>73 % </p>";
                cout << "<progress value=\"73\" max=\"100\">< /progress>";
                cout << "</td>";
                cout << "</tr>";
                cout << "</tbody>";
                cout << "</table>";
                cout << "</div>";
			}
        } file.close(); delete[] line;
	}
	return 0;
}
