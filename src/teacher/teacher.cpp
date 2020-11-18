#include "teacher.h"
#include <unistd.h>
#include "orderFile.h"

Teacher::Teacher()
{
	cout << "This is Teacher empty constructor" << endl;
}

Teacher::Teacher(int id, string name, string pwd)
{
	cout << "Teacher constructor" << endl;
	this->m_EmpId = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "欢迎教师代表：" << this->m_Name << "登录" << endl;
	cout << "\t\t  ---------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            1.查看所有预约      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            2.进入审核预约      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            0.注销登录          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t  ---------------------------------\n";
	cout << "请输入您的操作：" << endl;
}

void Teacher::showAllOrder()
{
	//创建order的对象,从中拿到所有的对象信息.然后展示出来.
	OrderFile of;
	int index = 0;
	//对于map有两种显示方法,第一种类似键值对,像数组一样,第二种使用迭代器
	for (map<int, map<string, string>>::iterator it = of.m_orderData.begin();
			it != of.m_orderData.end(); it++)
	{
		cout << "第" << index++ << "个申请: ";
		for (map<string, string>::iterator mid = it->second.begin();
				mid != it->second.end(); mid++)
		{
			cout << mid->first << ":" << mid->second << " ";
		}
		cout << "\r\n" << endl;
	}
}

void Teacher::validOrder()
{
	//显示所有的order,需要按照顺序来显示
	OrderFile of;
	int index = 0;
	string status = "";
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << "第" << (++index) << "条信息";
		cout << "date:" << of.m_orderData[i]["date"];
		cout << " " << "interval:"
				<< (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " " << "stuId:" << of.m_orderData[i]["stuId"];
		cout << " " << "stuName:" << of.m_orderData[i]["stuName"];
		cout << " " << "roomId:" << of.m_orderData[i]["roomId"];
		cout << " " << "status:";
		if (of.m_orderData[i]["status"] == "1")
		{
			status = "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status = "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status = "预约失败";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status = "取消";
		}
		cout << status;

		cout << "\r" << endl;
	}
	//提示使能有效相关的order
	cout << "请输入序号,对相应的信息进行批准" << endl;
	int select = 0;
	cin >> select;
	if (select == 0) //退出
	{
		cout << "输入为0,退出系统" << endl;
		return;
	}
	else if (select >= 1 && select <= of.m_Size)
	{
		of.m_orderData[select - 1]["status"] = "2";
		of.updateOrder();
	}

	pause();
}

void teacherMenu(Identity*& teacher)
{
	//显示教室子菜单.
	teacher->operMenu();

	Teacher* tea = (Teacher*) teacher;
	int select = 0;
	while (true)
	{
		cin >> select;
		switch (select)
		{
		case 0: //注销
			delete teacher;
			return;
		case 1: //查看所有预约 //进入查看所有预约菜单
			tea->showAllOrder();
			break;
		case 2: //进入审核预约 //进入审核预约菜单
			tea->validOrder();
			break;
		default:
			cout << "输入错误,请重新输入" << endl;
			break;
		}

	}

}
