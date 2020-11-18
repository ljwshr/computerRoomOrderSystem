#include <iostream>
#include "student.h"
#include <unistd.h>
#include <fstream>
#include "orderFile.h"

//在外部实现默认构造函数
Student::Student()
{
	cout << ("this is Student constructor") << endl;
}

Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	//获取机房信息,初始化机房容器
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "机房文件打开失败" << endl;
		return;
	}
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		Com.push_back(c);
	}
	ifs.close();
}

void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->m_Name << "登录" << endl;
	cout << "\t\t  ---------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            1.申请预约          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            2.查看我的预约      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            3.查看所有预约      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            4.取消预约          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            0.注销登录          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t  ---------------------------------\n";
	cout << "请输入您的操作：" << endl;
}

void Student::applyOrder()
{
	cout << "机房开放时间为周一至周五" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	// 输入日期.
	cout << "请输入预约的日期" << endl;
	int date = 0;
	int interval = 0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		else
		{
			cout << "日期输入错误,请重新输入" << endl;
		}
	}
	//输入上午下午
	cout << "请选择上午还是下午";
	cout << "1. 上午";
	cout << "2. 下午";

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		else
		{
			cout << "输入错误,请重新输入" << endl;
		}
	}
	//选择机房
	cout << "请选择机房编号" << endl;
	for (vector<ComputerRoom>::iterator c = Com.begin(); c != Com.end(); c++)
	{
		cout << "机房编号:" << c->m_ComId << " 容量:" << c->m_MaxNum << endl;
	}
	unsigned int roomId;
	while (true)
	{
		cin >> roomId;
		if (roomId >= 1 && roomId <= Com.size())
		{
			break;
		}
		else
		{
			cout << "编号不对,请重新输入" << endl;
		}
	}
	//使用ofs进行操作.
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << roomId << " ";
	ofs << "status:" << 1 << "\r\n";

	ofs.close();
	cout << "预约成功,审核中" << endl;
}
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		return;
	}
	// 从order类当中读取相关的信息,遍历找到自己的预约,然后进行打印
	// 状态:1 审核中, 2 约成功, -1 预约失败. 0 取消
	bool is_booked = false;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == m_Id)
		{
			if (!is_booked)
			{
				is_booked = true;
				cout << "\r\n您的预约信息为: \r\n";
			}
			cout << "stuName:" << of.m_orderData[i]["stuName"];
			cout << " date:" << of.m_orderData[i]["date"];
			cout << " interval:"
					<< ((of.m_orderData[i]["interval"] == "1") ? "上午" : "下午");
			cout << " roomId:" << of.m_orderData[i]["roomId"];
			cout << " status:";
			if (of.m_orderData[i]["status"] == "1")
			{
				cout << "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				cout << "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				cout << "预约失败";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				cout << "预约取消";
			}
			cout << "\r\n";
		}
	}
	if (!is_booked)
	{
		cout << "无您的预约记录";
	}
	cout << endl;
	pause();
}
void Student::showAllOrder()
{
	OrderFile of;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (i == 0)
		{
			cout << "\r\n所有的预约信息为: \r\n";
		}
		cout << "stuName:" << of.m_orderData[i]["stuName"];
		cout << " date:" << of.m_orderData[i]["date"];
		cout << " interval:"
				<< ((of.m_orderData[i]["interval"] == "1") ? "上午" : "下午");
		cout << " roomId:" << of.m_orderData[i]["roomId"];
		cout << " status:";
		if (of.m_orderData[i]["status"] == "1")
		{
			cout << "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			cout << "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			cout << "预约失败";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			cout << "预约取消";
		}
		cout << "\r\n";
	}
	cout << endl;
	pause();
}

void Student::cancelOrder()
{
	//无预约记录
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "系统中无预约记录" << endl;
		return;
	}

	//查找输入该用户的预约记录
	cout << "审核中或以预约陈功的记录可以取消,请输入取消的记录" << endl;
	vector<int> v;
	//次处有两种方法来进行遍历,一种是通过txt,一种是通过map,显然通过map更好一点
	//使用 map进行遍历,也有两种遍历方法,第一种是使用iterator,第二种是通过下标[]
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id) // TODO:只记录审核和成功的
		{
			v.push_back(i);
		}
	}
	// 处理相关的取消记录
	cout << "请输入取消的记录,0代表返回" << endl;
	for (unsigned int j = 0; j < v.size(); j++)
	{
		cout << (j + 1) << " 条记录";
		cout << " date:" << of.m_orderData[v[j]]["date"];
		cout << " interval:" << of.m_orderData[v[j]]["interval"];
		cout << " stuName:" << of.m_orderData[v[j]]["stuName"];
		cout << " roomId:" << of.m_orderData[v[j]]["roomId"];
		cout << " status:" << of.m_orderData[v[j]]["status"];
		cout << "\r\n";
	}
	cout << endl;

	unsigned int select_cancel = 0;
	while (true)
	{
		cin >> select_cancel;
		if (select_cancel == 0)
		{
			cout << "退出" << endl;
			return;
		}

		if (select_cancel >= 1 && select_cancel <= v.size())
		{
			of.m_orderData[v[select_cancel - 1]]["status"] = "0";
			of.updateOrder();
			cout << "取消成功" << endl;
			break; //要迅速退出去,否则会再次清空文件?
		}
		else
		{
			cout << "输入错误,请重新输入" << endl;
		}
	}
}

void studentMenu(Identity*& student)
{
	while (true)
	{
		//学生菜单
		student->operMenu();
		Student* stu = (Student*) student;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1: //申请预约
			stu->applyOrder();
			break;
		case 2: //查看我的预约
			stu->showMyOrder();
			break;
		case 3: //查看所有的预约
			stu->showAllOrder();
			break;
		case 4: //取消预约
			stu->cancelOrder();
			break;
		case 0: //注销登录
			delete student;
			cout << "注销登录" << endl;
			return;
		default:
			break;
		}

	}
}
