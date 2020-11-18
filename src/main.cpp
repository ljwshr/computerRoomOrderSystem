#include <iostream>
#include <unistd.h> //Linux �����£����Ա��ּ�����������̨�ķ���
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
#include <fstream>
using namespace std;

//��¼����, ����1 �����ļ���,����2 �����������(����ص����ݿ⵱�в�����ص���Ա)
// ��ʵҲ����ͨ��һ��type��Ϣ,Ȼ���������ص��ļ�,��������,�����ڽ���,��¼ֻ�ܵ�¼,��Ҫ��ϵ�һ��
void LoginIn(string fileName, int type)
{
	//TODO: replace the type with enum.
	//����ָ��,����ָ���������
	Identity* person = nullptr;
	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);
	cout << "�ļ�������" << fileName << endl;
	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;
	//�ж����
	switch (type)
	{
	case 1: //ѧ������
		cout << "����������ѧ��:" << endl;
		cin >> id;
		break;
	case 2: //��ʦ����
		cout << "����������ְ����:" << endl;
		cin >> id;
		break;
	case 3: // ����Ա
		cout << "����Ա��¼" << endl;
		break;
	default:
		//������,�����Լ��ĳ������,��Ӧ����default
		throw("��¼��Ϣ�������Ͳ�����");
		break;
	}
	cout << "�������û���:" << endl;
	cin >> name;
	cout << "����������:" << endl;
	cin >> pwd;

	int fId;
	string fName;
	string fPwd;
	switch (type)
	{
	case 1: //ѧ�������֤
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ�!" << endl;
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
		return;
	case 2: //��ʦ�����֤
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��¼�ɹ�!" << endl;
				pause();
				person = new Teacher(id, name, pwd);
				return;
			}
		}
		return;
	case 3: //����Ա�����֤
		while (ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (name == fName && pwd == fPwd)
			{
				cout << "����Ա��֤��¼�ɹ�!" << endl;
				person = new Manager(name, pwd);
				//�������Ա��ݵ��Ӳ˵�
				managerMenu(person);
				return;
			}
		}
		return;
	default:
		throw("��¼��Ϣ�������Ͳ�����");
		break;
	}

	//���û����֤�ɹ�,���򽫻��ߵ�����
	cout << "��֤��¼ʧ��!" << endl;
	pause();
	return;

}
int main()
{
	int select = 0;
	string fileName;
	while (true)
	{
		cout << endl << "�������������" << endl;
		cout << "\t\t  ---------------------------------\n";
		cout << "\t\t |                              	|\n";
		cout << "\t\t |            1.ѧ������                  	|\n";
		cout << "\t\t |                                	|\n";
		cout << "\t\t |            2.��    ʦ          		|\n";
		cout << "\t\t |                                	|\n";
		cout << "\t\t |            3.�� �� Ա          		|\n";
		cout << "\t\t |                              	|\n";
		cout << "\t\t |            0.��    ��          		|\n";
		cout << "\t\t |                             	|\n";
		cout << "\t\t  ---------------------------------\n";
		cout << "����������ѡ��";

		cin >> select; //�����û�������
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
			cout << "��ӭ��һ��ʹ��" << endl;
			break;
		default:
			cout << "������������������" << endl;
			system("clear");
			break;
		}
	}
	system("clear");

	return 0;
}
