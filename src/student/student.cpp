#include <iostream>
#include "student.h"
#include <unistd.h>
#include <fstream>
#include "orderFile.h"

//���ⲿʵ��Ĭ�Ϲ��캯��
Student::Student()
{
	cout << ("this is Student constructor") << endl;
}

Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	//��ȡ������Ϣ,��ʼ����������
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�����ļ���ʧ��" << endl;
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
	cout << "��ӭѧ������" << this->m_Name << "��¼" << endl;
	cout << "\t\t  ---------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            1.����ԤԼ          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            2.�鿴�ҵ�ԤԼ      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            3.�鿴����ԤԼ      |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            4.ȡ��ԤԼ          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |            0.ע����¼          |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t  ---------------------------------\n";
	cout << "���������Ĳ�����" << endl;
}

void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	// ��������.
	cout << "������ԤԼ������" << endl;
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
			cout << "�����������,����������" << endl;
		}
	}
	//������������
	cout << "��ѡ�����绹������";
	cout << "1. ����";
	cout << "2. ����";

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		else
		{
			cout << "�������,����������" << endl;
		}
	}
	//ѡ�����
	cout << "��ѡ��������" << endl;
	for (vector<ComputerRoom>::iterator c = Com.begin(); c != Com.end(); c++)
	{
		cout << "�������:" << c->m_ComId << " ����:" << c->m_MaxNum << endl;
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
			cout << "��Ų���,����������" << endl;
		}
	}
	//ʹ��ofs���в���.
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	if (!ofs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << roomId << " ";
	ofs << "status:" << 1 << "\r\n";

	ofs.close();
	cout << "ԤԼ�ɹ�,�����" << endl;
}
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		return;
	}
	// ��order�൱�ж�ȡ��ص���Ϣ,�����ҵ��Լ���ԤԼ,Ȼ����д�ӡ
	// ״̬:1 �����, 2 Լ�ɹ�, -1 ԤԼʧ��. 0 ȡ��
	bool is_booked = false;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == m_Id)
		{
			if (!is_booked)
			{
				is_booked = true;
				cout << "\r\n����ԤԼ��ϢΪ: \r\n";
			}
			cout << "stuName:" << of.m_orderData[i]["stuName"];
			cout << " date:" << of.m_orderData[i]["date"];
			cout << " interval:"
					<< ((of.m_orderData[i]["interval"] == "1") ? "����" : "����");
			cout << " roomId:" << of.m_orderData[i]["roomId"];
			cout << " status:";
			if (of.m_orderData[i]["status"] == "1")
			{
				cout << "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				cout << "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				cout << "ԤԼʧ��";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				cout << "ԤԼȡ��";
			}
			cout << "\r\n";
		}
	}
	if (!is_booked)
	{
		cout << "������ԤԼ��¼";
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
			cout << "\r\n���е�ԤԼ��ϢΪ: \r\n";
		}
		cout << "stuName:" << of.m_orderData[i]["stuName"];
		cout << " date:" << of.m_orderData[i]["date"];
		cout << " interval:"
				<< ((of.m_orderData[i]["interval"] == "1") ? "����" : "����");
		cout << " roomId:" << of.m_orderData[i]["roomId"];
		cout << " status:";
		if (of.m_orderData[i]["status"] == "1")
		{
			cout << "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			cout << "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			cout << "ԤԼʧ��";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			cout << "ԤԼȡ��";
		}
		cout << "\r\n";
	}
	cout << endl;
	pause();
}

void Student::cancelOrder()
{
	//��ԤԼ��¼
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "ϵͳ����ԤԼ��¼" << endl;
		return;
	}

	//����������û���ԤԼ��¼
	cout << "����л���ԤԼ�¹��ļ�¼����ȡ��,������ȡ���ļ�¼" << endl;
	vector<int> v;
	//�δ������ַ��������б���,һ����ͨ��txt,һ����ͨ��map,��Ȼͨ��map����һ��
	//ʹ�� map���б���,Ҳ�����ֱ�������,��һ����ʹ��iterator,�ڶ�����ͨ���±�[]
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id) // TODO:ֻ��¼��˺ͳɹ���
		{
			v.push_back(i);
		}
	}
	// ������ص�ȡ����¼
	cout << "������ȡ���ļ�¼,0������" << endl;
	for (unsigned int j = 0; j < v.size(); j++)
	{
		cout << (j + 1) << " ����¼";
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
			cout << "�˳�" << endl;
			return;
		}

		if (select_cancel >= 1 && select_cancel <= v.size())
		{
			of.m_orderData[v[select_cancel - 1]]["status"] = "0";
			of.updateOrder();
			cout << "ȡ���ɹ�" << endl;
			break; //ҪѸ���˳�ȥ,������ٴ�����ļ�?
		}
		else
		{
			cout << "�������,����������" << endl;
		}
	}
}

void studentMenu(Identity*& student)
{
	while (true)
	{
		//ѧ���˵�
		student->operMenu();
		Student* stu = (Student*) student;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1: //����ԤԼ
			stu->applyOrder();
			break;
		case 2: //�鿴�ҵ�ԤԼ
			stu->showMyOrder();
			break;
		case 3: //�鿴���е�ԤԼ
			stu->showAllOrder();
			break;
		case 4: //ȡ��ԤԼ
			stu->cancelOrder();
			break;
		case 0: //ע����¼
			delete student;
			cout << "ע����¼" << endl;
			return;
		default:
			break;
		}

	}
}
