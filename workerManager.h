#pragma once  //��ֹͷ�ļ��ظ�����
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
	Worker** workerArray;  //һ�������ָ�룬��������ָ��Worker��ָ��
	bool flag;  //�ļ��Ƿ�Ϊ��
};