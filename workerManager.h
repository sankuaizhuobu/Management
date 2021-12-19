#pragma once  //防止头文件重复包含
#include <iostream>
#include "Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
using namespace std;

class workerManager
{
public:
	int getSize();
	void initWorker();
	workerManager();
	~workerManager();
	void showMenu();
	void exitSystem();
	void save();
	void addWorker();
	void showWorker();
	int isExist(int id);
	void deleteWorker();
	void modifyWorker();
	void searchWorker();

	int size;
	Worker** workerArray;  //一个数组的指针，数组中是指向Worker的指针
	bool flag;  //文件是否为空
};