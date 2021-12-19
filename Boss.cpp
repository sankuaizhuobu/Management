#include "Boss.h"

Boss::Boss(int id, string name, int DeId)
{
	this->id = id;
	this->name = name;
	this->DeId = DeId;
}

void Boss::showInfo()
{
	cout << "编号：" << this->id
		<< "\t姓名：" << this->name
		<< "\t岗位：" << this->getDeName()
		<< "\t岗位职责：给经理指派任务" << endl;
}
string Boss::getDeName()
{
	return string("老板");
}
