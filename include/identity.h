#pragma once
#include <iostream>
#include <string>

using namespace std;

//身份抽象类
class Identity
{
public:
	//操作菜单,纯虚函数
	//每个子类都有自己单独的操作菜单. 自己去单独实现.
	virtual void operMenu()=0;
	string m_Name;
	string m_Pwd;
};
