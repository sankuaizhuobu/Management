#include "workerManager.h"
#include<fstream>
#define FILENAME "workers.txt"

int workerManager::getSize()
{
	ifstream f;
	f.open(FILENAME, ios::in);

	int id;
	string name;
	int DeId;

	int num = 0;

	while (f >> id && f >> name && f >> DeId)  //�������ݶ�����˳�ѭ��
	{
		num++;
	}
	return num;
	f.close();
}

void workerManager::initWorker()
{
	ifstream f;
	f.open(FILENAME, ios::in);

	int id;
	string name;
	int DeId;

	int i = 0;
	while (f >> id && f >> name && f >> DeId)
	{
		Worker* worker = NULL;
		if (DeId == 1)  worker = new Employee(id, name, DeId);
		else if (DeId == 2)  worker = new Manager(id, name, DeId);
		else if (DeId == 3)  worker = new Boss(id, name, DeId);

		this->workerArray[i++] = worker;   //���ļ����ݶ�������
	}
	f.close();
}

workerManager::workerManager()
{
	ifstream f;
	f.open(FILENAME, ios::in);

	if (!f.is_open())  //�ļ�������
	{
		cout << "�ļ������ڣ�" << endl;
		this->size = 0;
		this->flag = true;
		this->workerArray = NULL;
		f.close();
		return;
	}

	char ch;
	f >> ch;
	if (f.eof())  //��һ���ַ��������EOF���ļ����ڵ�Ϊ��
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->size = 0;
		this->flag = true;
		this->workerArray = NULL;
		f.close();
		return;
	}

	//�ļ�������������
	int num = this->getSize();
	cout << "ְ������Ϊ��" << num << endl;
	this->size = num;
	this->workerArray = new Worker * [this->size];  //����ְ�����飨���캯����
	initWorker();      //���ļ����ݶ�������
}

workerManager::~workerManager()
{
	if (this->workerArray != NULL)  //�������� �ֶ����١��ͷ�
	{
		delete[] this->workerArray;
		this->workerArray = NULL;
	}
}

void workerManager::showMenu()
{
	cout << "*******************************" << endl;
	cout << "*******************************" << endl;
	cout << "******     0���˳�       ******" << endl;
	cout << "****       1�����Ա��     ****" << endl;
	cout << "***        2����ʾԱ��      ***" << endl;
	cout << "***        3��ɾ��Ա��      ***" << endl;
	cout << "***        4���޸�Ա��      ***" << endl;
	cout << "***        5������Ա��      ***" << endl;
	cout << "****       6������         ****" << endl;
	cout << "******     7������ĵ�   ******" << endl;
	cout << "*******************************" << endl;
	cout << "*******************************" << endl;
}

//0���˳�
void workerManager::exitSystem()
{
	cout << "��ӭ�´�������" << endl;
	system("pause");
	exit(0);  //�˳�����
}

//1�����Ա��
void workerManager::save()
{
	ofstream f;
	f.open(FILENAME, ios::out);

	for (int i = 0; i < this->size; ++i)
	{
		f << this->workerArray[i]->id << " "
			<< this->workerArray[i]->name << " "
			<< this->workerArray[i]->DeId << endl;
	}
	f.close();
}

void workerManager::addWorker()
{
	cout << "����������������" << endl;
	int add = 0;
	cin >> add;

	if (add > 0)
	{
		int newSize = this->size + add;
		Worker** newSpace = new Worker * [newSize];  //�¿��ٶ����ռ�, newSpaceΪWorker*����

		if (this->workerArray != NULL)  //ԭ������Ϣ����
		{
			for (int i = 0; i < newSize; ++i)
			{
				newSpace[i] = this->workerArray[i];
			}
		}
		for (int i = 0; i < add; ++i)
		{
			int id;
			string name;
			int pos;

			cout << "�������" << i + 1 << "����ְԱ��ţ�" << endl;
			cin >> id;
			while (isExist(id) != -1)
			{
				cout << "�ñ���Ѵ��ڣ����������룺" << endl;
				cin >> id;
			}
			cout << "�������" << i + 1 << "����ְԱ������" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "����ְԱ��λ��" << endl;
			cout << "1-Ա��" << endl;
			cout << "2-����" << endl;
			cout << "3-�ϰ�" << endl;
			cin >> pos;

			Worker* worker = NULL;
			switch (pos)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->size + i] = worker;  //����ְ����������
		}
		delete[] this->workerArray;  //�������µ�Worker*���飬 ��Ҫ�ͷžɵ�����
		this->workerArray = newSpace;  //ָ���¿ռ�
		this->size = newSize;

		cout << "�ɹ����" << add << "����ְ����" << endl;
		this->flag = false;
		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");  //����������������ص��˵�
	system("cls");
}

//2����ʾԱ��
void workerManager::showWorker()
{
	if (this->flag)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->size; i++)
		{
			this->workerArray[i]->showInfo();  //���ö�̬���ýӿ�
		}
	}
	system("pause"); 
	system("cls");
}

//3��ɾ��Ա��
int workerManager::isExist(int id)
{
	int i = -1;
	for (int j = 0; j < this->size; ++j)
	{
		if (this->workerArray[j]->id == id)
		{
			i = j;
			break;
		}
	}
	return i;
}

void workerManager::deleteWorker()
{
	if (this->flag == 1)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	int i;
	cout << "������Ҫɾ����ְ����ţ�" << endl;
	cin >> i;
	int pos = isExist(i);
	if (pos == -1)
	{
		cout << "δ�ҵ���ְ����" << endl;
	}
	else
	{
		this->workerArray[pos]->showInfo();
		for (int j = pos; j < this->size - 1; ++j)
		{
			this->workerArray[j] = this->workerArray[j + 1];
		}
		this->size--;
		this->save();
		cout << "ɾ���ɹ���" << endl;
	}
	system("pause");
	system("cls");
}

//4���޸�Ա��
void workerManager::modifyWorker()
{
	if (this->flag == 1)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else
	{
		int i;
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		cin >> i;
		int pos = isExist(i);
		if (pos == -1)
		{
			cout << "δ�ҵ���ְ����" << endl;
		}
		else
		{
			int id;
			string name;
			int DeId;
			cout << "�ҵ�" << i << "��Ա��" << endl;
			this->workerArray[pos]->showInfo();

			cout << "�����µı�ţ�" << endl;
			cin >> id;
			cout << "�����µ�������" << endl;
			cin >> name;
			cout << "�����µĸ�λ��" << endl;
			cout << "1-Ա��" << endl;
			cout << "2-����" << endl;
			cout << "3-�ϰ�" << endl;
			cin >> DeId;

			Worker* worker = NULL;
			switch (DeId)
			{
			case 1:
				worker = new Employee(id, name, DeId);
				break;
			case 2:
				worker = new Manager(id, name, DeId);
				break;
			case 3:
				worker = new Boss(id, name, DeId);
				break;
			default:
				break;
			}
			this->workerArray[pos] = worker;
			this->save();
			cout << "�޸ĳɹ���" << endl;
		}
	}
	system("pause");
	system("cls");
}

//5������Ա��
void  workerManager::searchWorker()
{
	if (this->flag == 1)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1-����Ų���" << endl;
		cout << "2-����������" << endl;
		int select;
		cin >> select;
		while (1)
		{
			if (select == 1)
			{
				int i;
				cout << "ְ����ţ�" << endl;
				cin >> i;
				int pos = isExist(i);
				if (pos == -1)
				{
					cout << "δ�ҵ���ְ����" << endl;
				}
				else
				{
					this->workerArray[pos]->showInfo();
				}
				break;
			}
			else if (select == 2)
			{
				string name;
				int flag = 0;
				cout << "������" << endl;
				cin >> name;
				for (int i = 0; i < this->size; ++i)
				{
					if (this->workerArray[i]->name == name)
					{
						flag = 1;
						this->workerArray[i]->showInfo();
					}
				}
				if (flag == 0)
				{
					cout << "δ�ҵ���ְ����" << endl;
				}
				break;
			}
			else
			{
				cout << "���Ҵ������������룺" << endl;
				cin >> select;
			}
		}
	}
	system("pause");
	system("cls");
}