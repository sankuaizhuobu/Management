#include "Boss.h"

Boss::Boss(int id, string name, int DeId)
{
	this->id = id;
	this->name = name;
	this->DeId = DeId;
}

void Boss::showInfo()
{
	cout << "��ţ�" << this->id
		<< "\t������" << this->name
		<< "\t��λ��" << this->getDeName()
		<< "\t��λְ�𣺸�����ָ������" << endl;
}
string Boss::getDeName()
{
	return string("�ϰ�");
}
