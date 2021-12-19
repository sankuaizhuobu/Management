#include "Manager.h"

Manager::Manager(int id, string name, int DeId)
{
	this->id = id;
	this->name = name;
	this->DeId = DeId;
}

void Manager::showInfo()
{
	cout << "编号：" << this->id
		<< "\t姓名：" << this->name
		<< "\t岗位：" << this->getDeName()
		<< "\t岗位职责：完成老板指定的任务，并下发给员工" << endl;
}
string Manager::getDeName()
{
	return string("经理");
}