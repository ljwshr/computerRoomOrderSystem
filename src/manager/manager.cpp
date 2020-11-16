#include "manager.h"
#include <unistd.h>
#include <globalFile.h>
#include <fstream>
#include <algorithm>

Manager::Manager()
{
	cout << "This is Manager constructor" << endl;
	this->initVector();
}
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器
	this->initVector();
}

Manager::~Manager()
{
	cout << "调用析构Manager函数" << endl;
}

void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录" << endl;
	cout << "\t\t  ---------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            1.添加账号          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            2.查看账号          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            3.查看机房          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            4.清空预约          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            0.注销登录          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t  ---------------------------------\n";
	cout << "请输入您的操作：";
}

void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1. 添加学生" << endl;
	cout << "2. 添加教师" << endl;
	cout << "0. 退出" << endl;

	string fileName; //操作的文件名
	string tip; //提示id号
	string errTips;

	ofstream ofs; //文件操作对象
	int select = 0;
	cin >> select; //接受用户的选项
	if (select == 1)
	{
		fileName = SUTDENT_FILE;
		tip = "请输入学号:";
		errTips = "学号重复,请重新输入";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工编号:";
		errTips = "职工号重复,请重新输入";
	}
	else
	{
		return;
	}

	cout << tip << endl;
	int id;
	string name;
	string pwd;
	//如果输入的id有重复,那么就一直循环等输入
	while (true)
	{
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		if (ret)
		{
			cout << errTips << endl;
		}
		else
		{
			break;
		}
	}

	// 利用追加的方式 写文件
	ofs.open(fileName, ios::out | ios::app);

	cout << "请输入姓名:" << endl;
	cin >> name;

	cout << "请输入密码:" << endl;
	cin >> pwd;

	//向文件占用添加数据
	ofs << " " << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;

	ofs.close();
	//bug:刚刚添加的账号,再次添加,还能够添加进去,所以,每次添加完后,需要重新对容器进行初始化
	this->initVector();

}

void printStudent(Student & stu)
{
	cout << "学号:" << stu.m_Id << " 姓名:" << stu.m_Name << " 密码:" << stu.m_Pwd
			<< endl;
}
void printTeacher(Teacher & tea)
{
	cout << "编号:" << tea.m_EmpId << " 姓名:" << tea.m_Name << " 密码:" << tea.m_Pwd
			<< endl;
}
void Manager::showPerson()
{
	cout << "请选择查看的内容:" << endl;
	cout << "1. 查看所有学生" << endl;
	cout << "2. 查看所有老师" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//查看学生如下:
		cout << "所有学生信息如下:" << endl;
		cout << this->vStu.size() << endl;
		//pause();
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "所有老师信息如下:" << endl;
		cout << this->vTea.size() << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
}

void Manager::showComputer()
{
}

void Manager::cleanFile()
{

}
void Manager::initVector()
{
	//确保容器清空状态
	vStu.clear();
	vTea.clear();
	//读取学生信息
	ifstream ifs;
	ifs.open(SUTDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "读取学生文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//测试
	cout << "当前学生数量为:" << vStu.size() << endl;
	ifs.close();
	//读取老师信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "读取教师文件读取失败" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//测试
	cout << "当前教师数量为" << vTea.size() << endl;
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end();
				it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end();
				it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}

void managerMenu(Identity*& manager) // 是个引用(类似于指针的地址),然后将其转换成实体
{
	while (true)
	{
		//调用管理员子菜单,虚函数,创建的是manager对象,所以调用对象的方法
		manager->operMenu();
		//将父类指针,转为子类指针,调用子类里其他接口
		Manager* man = (Manager*) manager;
		//man->initVector();
		//cout << man->vStu.size() << endl; // TODO: 能够打印出来,这就对了,应该是之前没有去清空重新编译的事情>
		//cout << man->vStu[0].m_Name << endl;
		//pause();

		int select = 0;
		//接受用户的选项
		cin >> select;
		switch (select)
		{
		case 1:		//添加账号
			cout << "添加账号" << endl;
			man->addPerson();
			break;
		case 2:		//查看账号
			cout << "查看账号" << endl;
			man->showPerson();
			break;
		case 3:		//查看机房信息
			cout << "查看机房" << endl;
			man->showComputer();
			break;
		case 4:		//清空预约
			cout << "清空预约" << endl;
			man->cleanFile();
			break;
		default:		//销毁堆区对象
			delete man;		//销毁堆区对象,不会调用析构函数.如果是
			cout << "注销成功" << endl;
			break;
		}
		return;		//如果不加return,会重复创建manager,导致出错.
	}
}

