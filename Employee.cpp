#include "Employee.h"

Employee::Employee(int id, string name, int DeId)
{
	this->id = id;
	this->name = name;
	this->DeId = DeId;
}

void Employee::showInfo()
{
	cout << "��ţ�" << this->id
		<< "\t������" << this->name
		<< "\t��λ��" << this->getDeName()
		<< "\t��λְ����ɾ���ָ��������" << endl;
}

string  Employee::getDeName()
{
	return string("Ա��");
}