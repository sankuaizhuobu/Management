#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;

class Employee:public Worker
{
public:
	Employee(int id, string name, int DeId);

	virtual void showInfo();
	virtual string getDeName();
};

