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

	while (f >> id && f >> name && f >> DeId)  //所有数据读完会退出循环
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

		this->workerArray[i++] = worker;   //将文件数据读入数组
	}
	f.close();
}

workerManager::workerManager()
{
	ifstream f;
	f.open(FILENAME, ios::in);

	if (!f.is_open())  //文件不存在
	{
		cout << "文件不存在！" << endl;
		this->size = 0;
		this->flag = true;
		this->workerArray = NULL;
		f.close();
		return;
	}

	char ch;
	f >> ch;
	if (f.eof())  //读一个字符，如果是EOF：文件存在但为空
	{
		cout << "文件为空！" << endl;
		this->size = 0;
		this->flag = true;
		this->workerArray = NULL;
		f.close();
		return;
	}

	//文件存在且有数据
	int num = this->getSize();
	cout << "职工人数为：" << num << endl;
	this->size = num;
	this->workerArray = new Worker * [this->size];  //创建职工数组（构造函数）
	initWorker();      //将文件数据读入数组
}

workerManager::~workerManager()
{
	if (this->workerArray != NULL)  //堆区数据 手动开辟、释放
	{
		delete[] this->workerArray;
		this->workerArray = NULL;
	}
}

void workerManager::showMenu()
{
	cout << "*******************************" << endl;
	cout << "*******************************" << endl;
	cout << "******     0、退出       ******" << endl;
	cout << "****       1、添加员工     ****" << endl;
	cout << "***        2、显示员工      ***" << endl;
	cout << "***        3、删除员工      ***" << endl;
	cout << "***        4、修改员工      ***" << endl;
	cout << "***        5、查找员工      ***" << endl;
	cout << "****       6、排序         ****" << endl;
	cout << "******     7、清空文档   ******" << endl;
	cout << "*******************************" << endl;
	cout << "*******************************" << endl;
}

//0、退出
void workerManager::exitSystem()
{
	cout << "欢迎下次再来！" << endl;
	system("pause");
	exit(0);  //退出程序
}

//1、添加员工
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
	cout << "请输入增加人数：" << endl;
	int add = 0;
	cin >> add;

	if (add > 0)
	{
		int newSize = this->size + add;
		Worker** newSpace = new Worker * [newSize];  //新开辟堆区空间, newSpace为Worker*数组

		if (this->workerArray != NULL)  //原来的信息拷贝
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

			cout << "请输入第" << i + 1 << "个新职员编号：" << endl;
			cin >> id;
			while (isExist(id) != -1)
			{
				cout << "该编号已存在！请重新输入：" << endl;
				cin >> id;
			}
			cout << "请输入第" << i + 1 << "个新职员姓名：" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个新职员岗位：" << endl;
			cout << "1-员工" << endl;
			cout << "2-经理" << endl;
			cout << "3-老板" << endl;
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
			newSpace[this->size + i] = worker;  //将新职工保存起来
		}
		delete[] this->workerArray;  //开辟了新的Worker*数组， 就要释放旧的数组
		this->workerArray = newSpace;  //指向新空间
		this->size = newSize;

		cout << "成功添加" << add << "名新职工！" << endl;
		this->flag = false;
		this->save();
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	system("pause");  //按任意键后，清屏，回到菜单
	system("cls");
}

//2、显示员工
void workerManager::showWorker()
{
	if (this->flag)
	{
		cout << "文件不存在，或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->size; i++)
		{
			this->workerArray[i]->showInfo();  //利用多态调用接口
		}
	}
	system("pause"); 
	system("cls");
}

//3、删除员工
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
		cout << "文件不存在，或记录为空！" << endl;
	}
	int i;
	cout << "请输入要删除的职工编号：" << endl;
	cin >> i;
	int pos = isExist(i);
	if (pos == -1)
	{
		cout << "未找到该职工！" << endl;
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
		cout << "删除成功！" << endl;
	}
	system("pause");
	system("cls");
}

//4、修改员工
void workerManager::modifyWorker()
{
	if (this->flag == 1)
	{
		cout << "文件不存在，或记录为空！" << endl;
	}
	else
	{
		int i;
		cout << "请输入要修改的职工编号：" << endl;
		cin >> i;
		int pos = isExist(i);
		if (pos == -1)
		{
			cout << "未找到该职工！" << endl;
		}
		else
		{
			int id;
			string name;
			int DeId;
			cout << "找到" << i << "号员工" << endl;
			this->workerArray[pos]->showInfo();

			cout << "输入新的编号：" << endl;
			cin >> id;
			cout << "输入新的姓名：" << endl;
			cin >> name;
			cout << "输入新的岗位：" << endl;
			cout << "1-员工" << endl;
			cout << "2-经理" << endl;
			cout << "3-老板" << endl;
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
			cout << "修改成功！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//5、查找员工
void  workerManager::searchWorker()
{
	if (this->flag == 1)
	{
		cout << "文件不存在，或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1-按编号查找" << endl;
		cout << "2-按姓名查找" << endl;
		int select;
		cin >> select;
		while (1)
		{
			if (select == 1)
			{
				int i;
				cout << "职工编号：" << endl;
				cin >> i;
				int pos = isExist(i);
				if (pos == -1)
				{
					cout << "未找到该职工！" << endl;
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
				cout << "姓名：" << endl;
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
					cout << "未找到该职工！" << endl;
				}
				break;
			}
			else
			{
				cout << "查找错误！请重新输入：" << endl;
				cin >> select;
			}
		}
	}
	system("pause");
	system("cls");
}