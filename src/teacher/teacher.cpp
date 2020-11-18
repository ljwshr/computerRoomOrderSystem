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
	cout << "��ӭ��ʦ����" << this->m_Name << "��¼" << endl;
	cout << "\t\t  ---------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            1.�鿴����ԤԼ      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            2.�������ԤԼ      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            0.ע����¼          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t  ---------------------------------\n";
	cout << "���������Ĳ�����" << endl;
}

void Teacher::showAllOrder()
{
	//����order�Ķ���,�����õ����еĶ�����Ϣ.Ȼ��չʾ����.
	OrderFile of;
	int index = 0;
	//����map��������ʾ����,��һ�����Ƽ�ֵ��,������һ��,�ڶ���ʹ�õ�����
	for (map<int, map<string, string>>::iterator it = of.m_orderData.begin();
			it != of.m_orderData.end(); it++)
	{
		cout << "��" << index++ << "������: ";
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
	//��ʾ���е�order,��Ҫ����˳������ʾ
	OrderFile of;
	int index = 0;
	string status = "";
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << "��" << (++index) << "����Ϣ";
		cout << "date:" << of.m_orderData[i]["date"];
		cout << " " << "interval:"
				<< (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " " << "stuId:" << of.m_orderData[i]["stuId"];
		cout << " " << "stuName:" << of.m_orderData[i]["stuName"];
		cout << " " << "roomId:" << of.m_orderData[i]["roomId"];
		cout << " " << "status:";
		if (of.m_orderData[i]["status"] == "1")
		{
			status = "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status = "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status = "ԤԼʧ��";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status = "ȡ��";
		}
		cout << status;

		cout << "\r" << endl;
	}
	//��ʾʹ����Ч��ص�order
	cout << "���������,����Ӧ����Ϣ������׼" << endl;
	int select = 0;
	cin >> select;
	if (select == 0) //�˳�
	{
		cout << "����Ϊ0,�˳�ϵͳ" << endl;
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
	//��ʾ�����Ӳ˵�.
	teacher->operMenu();

	Teacher* tea = (Teacher*) teacher;
	int select = 0;
	while (true)
	{
		cin >> select;
		switch (select)
		{
		case 0: //ע��
			delete teacher;
			return;
		case 1: //�鿴����ԤԼ //����鿴����ԤԼ�˵�
			tea->showAllOrder();
			break;
		case 2: //�������ԤԼ //�������ԤԼ�˵�
			tea->validOrder();
			break;
		default:
			cout << "�������,����������" << endl;
			break;
		}

	}

}
