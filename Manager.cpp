#include "Manager.h"

Manager::Manager(int id, string name, int DeId)
{
	this->id = id;
	this->name = name;
	this->DeId = DeId;
}

void Manager::showInfo()
{
	cout << "��ţ�" << this->id
		<< "\t������" << this->name
		<< "\t��λ��" << this->getDeName()
		<< "\t��λְ������ϰ�ָ�������񣬲��·���Ա��" << endl;
}
string Manager::getDeName()
{
	return string("����");
}