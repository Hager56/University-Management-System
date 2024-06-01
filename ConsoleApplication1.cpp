#include <iostream>
#include <iomanip> 
#include <string>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>
#include "needed_classes.h"
#include<windows.h>
using namespace std;
int main()
{
	files_d* data2 = new files_d();
	University* uni = new University(data2);
	uni->fitchData();
	admin Controller(uni);
	uni->means(Controller.get_mean());
	while (true)
	{
		system("cls");
		string tmp[2];
		cout << "Let the Name q to Exit\n";
		cout << "Id : ";
		cin >> tmp[0];
		if (tmp[0] == "q")
		{
			break;
		}
		cout << "Password : ";
		cin >> tmp[1];
		Controller.login(tmp);
		uni->login(tmp);
	}
	Controller.~admin();
	uni->~University();
	data2->~files_d();
}