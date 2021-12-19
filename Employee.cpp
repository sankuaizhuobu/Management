#include "Employee.h"

Employee::Employee(int id, string name, int DeId)
{
	this->id = id;
	this->name = name;
	this->DeId = DeId;
}

void Employee::showInfo()
{
	cout << "编号：" << this->id
		<< "\t姓名：" << this->name
		<< "\t岗位：" << this->getDeName()
		<< "\t岗位职责：完成经理指定的任务" << endl;
}

string  Employee::getDeName()
{
	return string("员工");
}