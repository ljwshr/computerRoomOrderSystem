#include <iostream>
#include "orderFile.h"
#include <fstream>
using namespace std;

OrderFile::OrderFile()
{
	cout << "order���캯����������" << endl;
	//��ȡ������Ϣ,Ȼ�������������
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ԤԼ�ļ�ʧ��" << endl;
		ifs.close();
		return;
	}
	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	this->m_Size = 0;

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName
			&& ifs >> roomId && ifs >> status)
	{
		//����
//		cout<<date;
//		cout<<interval;
//		cout<<stuId;
//		cout<<stuName;
//		cout<<roomId;
//		cout<<status<<endl;
		//�������Ϣ�ŵ�map����
		string key;
		string value;
		map<string, string> m;
		//��ȡʱ���
		int pos = date.find(":");		// 4
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡ���
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡѧ��ID
		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡѧ������
		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡ�����
		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡ״̬
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��С��map���뵽���map����.
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();
	//����
//	for (map<int, map<string, string>>::iterator it = m_orderData.begin();
//			it != m_orderData.end(); it++)
//	{
//		cout << "����Ϊ" << it->first << "value = ";
//		for (map<string, string>::iterator mit = it->second.begin();
//				mit != it->second.end(); mit++)
//		{
//			cout << " key=" << mit->first << " value=" << mit->second << ";";
//		}
//		cout << "\r\n";
//	}
//	cout << endl;

	//��һ�ִ�ӡ����:
//	for (int i = 0; i < m_Size; i++)
//	{
//		cout << "date:" << m_orderData[i]["date"] << "";
//		cout << "interval:" << m_orderData[i]["interval"] << "";
//		cout << "stuId:" << m_orderData[i]["stuId"] << "";
//		cout << "stuName:" << m_orderData[i]["stuName"] << "";
//		cout << "roomId:" << m_orderData[i]["roomId"] << "";
//		cout << "status:" << m_orderData[i]["status"] << "";
//		cout << "\r\n";
//	}
//	cout << endl;

}

void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out);
	if (!ofs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	cout << "this_m_Size = " << this->m_Size << endl;
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << m_orderData[i]["date"] << " ";
		ofs << "interval:" << m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << m_orderData[i]["roomId"] << " ";
		ofs << "status:" << m_orderData[i]["status"] << "\r\n";

	}
	ofs.close();
}
