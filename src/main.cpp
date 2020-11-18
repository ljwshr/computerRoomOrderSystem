#include <iostream>
#include <unistd.h> //Linux 环境下，可以保持继续保留控制台的方法
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
#include <fstream>
using namespace std;

//登录功能, 参数1 操作文件名,参数2 操作身份类型(在相关的数据库当中查找相关的人员)
// 其实也可以通过一个type信息,然后关连到相关的文件,但是那样,不利于解耦,登录只管登录,不要耦合到一起
void LoginIn(string fileName, int type)
{
	//TODO: replace the type with enum.
	//父类指针,用于指向子类对象
	Identity* person = nullptr;
	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	cout << "文件名字是" << fileName << endl;
	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;
	//判断身份
	switch (type)
	{
	case 1: //学生代表
		cout << "请输入您的学号:" << endl;
		cin >> id;
		break;
	case 2: //教师代表
		cout << "请输入您的职工号:" << endl;
		cin >> id;
		break;
	case 3: // 管理员
		cout << "管理员登录" << endl;
		break;
	default:
		//理论上,经过自己的程序调用,不应该有default
		throw("登录信息传参类型不存在");
		break;
	}
	cout << "请输入用户名:" << endl;
	cin >> name;
	cout << "请输入密码:" << endl;
	cin >> pwd;

	int fId;
	string fName;
	string fPwd;
	switch (type)
	{
	case 1: //学生身份验证
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "学生验证登录成功!" << endl;
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
		return;
	case 2: //教师身份验证
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功!" << endl;
				pause();
				person = new Teacher(id, name, pwd);
				return;
			}
		}
		return;
	case 3: //管理员身份验证
		while (ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (name == fName && pwd == fPwd)
			{
				cout << "管理员验证登录成功!" << endl;
				person = new Manager(name, pwd);
				//进入管理员身份的子菜单
				managerMenu(person);
				return;
			}
		}
		return;
	default:
		throw("登录信息传参类型不存在");
		break;
	}

	//如果没有验证成功,程序将会走到这里
	cout << "验证登录失败!" << endl;
	pause();
	return;

}
int main()
{
	int select = 0;
	string fileName;
	while (true)
	{
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t  ---------------------------------\n";
		cout << "\t\t |                              	|\n";
		cout << "\t\t |            1.学生代表                  	|\n";
		cout << "\t\t |                                	|\n";
		cout << "\t\t |            2.老    师          		|\n";
		cout << "\t\t |                                	|\n";
		cout << "\t\t |            3.管 理 员          		|\n";
		cout << "\t\t |                              	|\n";
		cout << "\t\t |            0.退    出          		|\n";
		cout << "\t\t |                             	|\n";
		cout << "\t\t  ---------------------------------\n";
		cout << "请输入您的选择：";

		cin >> select; //接收用户的输入
		switch (select)
		{
		case 1: // student
			fileName = SUTDENT_FILE;
			LoginIn(fileName, select);
			break;
		case 2: // teacher
			break;
		case 3: // administrator
			fileName = ADMIN_FILE;
			LoginIn(fileName, select);
			break;
		case 0: // exit the system
			cout << "欢迎下一次使用" << endl;
			break;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("clear");
			break;
		}
	}
	system("clear");

	return 0;
}
