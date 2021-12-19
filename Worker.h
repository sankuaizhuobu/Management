#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
	virtual void showInfo() = 0;
	virtual string getDeName() = 0;

	int id;
	string name;
	int DeId;  //≤ø√≈±‡∫≈
};

