#include<iostream>
#include "workerManager.h"
#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
using namespace std;

int main()
{
	workerManager wm;
	int choice = 0;
	while (true)
	{
		wm.showMenu();
		cout << "ÇëÊäÈëÄãµÄÑ¡Ôñ£º" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.addWorker();
			break;
		case 2:
			wm.showWorker();
			break;
		case 3:
			wm.deleteWorker();
			break;
		case 4:
			wm.modifyWorker();
			break;
		case 5:
			wm.searchWorker();
			break; 
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}