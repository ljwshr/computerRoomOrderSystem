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
	//���ԤԼ��¼
	void cleanFile();
	//��ʼ������ // ���׿������ó�static,Ҳ���Բ����ó�,
	//������ó�static,��ôֻҪ�ǹ���Ա,���ܹ��������е���Ա
	//��ȡЧ�ʿ�,���ǽ��������׷ֿ�����Ȩ��.
	//��������ó�static,ÿ��manager���Ե�������Ȩ��,
	void initVector();
	//ѧ������
	vector<Student> vStu;
	//��ʦ����
	vector<Teacher> vTea;
	//����ظ� ����:����id,��������,����ֵ:(true �������ظ�,false,����û���ظ�)
	bool checkRepeat(int id, int type);
private:
};
void managerMenu(Identity*& manager);

