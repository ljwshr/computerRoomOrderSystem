#include <iostream>
using namespace std;
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include <vector>

class Manager: public Identity
{

public:
	Manager();
	Manager(string name, string pwd);
	virtual ~Manager();
	virtual void operMenu();
	void addPerson();
	void showPerson();
	void showComputer();
	//清空预约记录
	void cleanFile();
	//初始化容器 // 容易可以设置成static,也可以不设置成,
	//如果设置成static,那么只要是管理员,就能够看到所有的人员
	//读取效率快,但是将来不容易分开控制权限.
	//如果不设置成static,每个manager可以单独设置权限,
	void initVector();
	//学生容器
	vector<Student> vStu;
	//教师容器
	vector<Teacher> vTea;
	//检查重复 参数:传入id,传入类型,返回值:(true 代表有重复,false,代表没有重复)
	bool checkRepeat(int id, int type);
private:
};
void managerMenu(Identity*& manager);

