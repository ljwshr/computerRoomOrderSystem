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

	//��ʼ������
	this->initVector();
}

Manager::~Manager()
{
	cout << "��������Manager����" << endl;
}

void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼" << endl;
	cout << "\t\t  ---------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            1.����˺�          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            2.�鿴�˺�          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            3.�鿴����          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            4.���ԤԼ          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            0.ע����¼          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t  ---------------------------------\n";
	cout << "���������Ĳ�����";
}

void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1. ���ѧ��" << endl;
	cout << "2. ��ӽ�ʦ" << endl;
	cout << "0. �˳�" << endl;

	string fileName; //�������ļ���
	string tip; //��ʾid��
	string errTips;

	ofstream ofs; //�ļ���������
	int select = 0;
	cin >> select; //�����û���ѡ��
	if (select == 1)
	{
		fileName = SUTDENT_FILE;
		tip = "������ѧ��:";
		errTips = "ѧ���ظ�,����������";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "������ְ�����:";
		errTips = "ְ�����ظ�,����������";
	}
	else
	{
		return;
	}

	cout << tip << endl;
	int id;
	string name;
	string pwd;
	//��������id���ظ�,��ô��һֱѭ��������
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

	// ����׷�ӵķ�ʽ д�ļ�
	ofs.open(fileName, ios::out | ios::app);

	cout << "����������:" << endl;
	cin >> name;

	cout << "����������:" << endl;
	cin >> pwd;

	//���ļ�ռ���������
	ofs << " " << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;

	ofs.close();
	//bug:�ո���ӵ��˺�,�ٴ����,���ܹ���ӽ�ȥ,����,ÿ��������,��Ҫ���¶��������г�ʼ��
	this->initVector();

}

void printStudent(Student & stu)
{
	cout << "ѧ��:" << stu.m_Id << " ����:" << stu.m_Name << " ����:" << stu.m_Pwd
			<< endl;
}
void printTeacher(Teacher & tea)
{
	cout << "���:" << tea.m_EmpId << " ����:" << tea.m_Name << " ����:" << tea.m_Pwd
			<< endl;
}
void Manager::showPerson()
{
	cout << "��ѡ��鿴������:" << endl;
	cout << "1. �鿴����ѧ��" << endl;
	cout << "2. �鿴������ʦ" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//�鿴ѧ������:
		cout << "����ѧ����Ϣ����:" << endl;
		cout << this->vStu.size() << endl;
		//pause();
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "������ʦ��Ϣ����:" << endl;
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
	//ȷ���������״̬
	vStu.clear();
	vTea.clear();
	//��ȡѧ����Ϣ
	ifstream ifs;
	ifs.open(SUTDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ȡѧ���ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//����
	cout << "��ǰѧ������Ϊ:" << vStu.size() << endl;
	ifs.close();
	//��ȡ��ʦ��Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ȡ��ʦ�ļ���ȡʧ��" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//����
	cout << "��ǰ��ʦ����Ϊ" << vTea.size() << endl;
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

void managerMenu(Identity*& manager) // �Ǹ�����(������ָ��ĵ�ַ),Ȼ����ת����ʵ��
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�,�麯��,��������manager����,���Ե��ö���ķ���
		manager->operMenu();
		//������ָ��,תΪ����ָ��,���������������ӿ�
		Manager* man = (Manager*) manager;
		//man->initVector();
		//cout << man->vStu.size() << endl; // TODO: �ܹ���ӡ����,��Ͷ���,Ӧ����֮ǰû��ȥ������±��������>
		//cout << man->vStu[0].m_Name << endl;
		//pause();

		int select = 0;
		//�����û���ѡ��
		cin >> select;
		switch (select)
		{
		case 1:		//����˺�
			cout << "����˺�" << endl;
			man->addPerson();
			break;
		case 2:		//�鿴�˺�
			cout << "�鿴�˺�" << endl;
			man->showPerson();
			break;
		case 3:		//�鿴������Ϣ
			cout << "�鿴����" << endl;
			man->showComputer();
			break;
		case 4:		//���ԤԼ
			cout << "���ԤԼ" << endl;
			man->cleanFile();
			break;
		default:		//���ٶ�������
			delete man;		//���ٶ�������,���������������.�����
			cout << "ע���ɹ�" << endl;
			break;
		}
		return;		//�������return,���ظ�����manager,���³���.
	}
}

