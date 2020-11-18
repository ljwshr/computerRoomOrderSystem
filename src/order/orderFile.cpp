#include <iostream>
#include "orderFile.h"
#include <fstream>
using namespace std;

OrderFile::OrderFile()
{
	cout << "order构造函数被调用了" << endl;
	//获取所有信息,然后放在容器当中
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "打开预约文件失败" << endl;
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
		//测试
//		cout<<date;
//		cout<<interval;
//		cout<<stuId;
//		cout<<stuName;
//		cout<<roomId;
//		cout<<status<<endl;
		//将相关信息放到map当中
		string key;
		string value;
		map<string, string> m;
		//截取时间段
		int pos = date.find(":");		// 4
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//截取间隔
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//获取学生ID
		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//获取学生名字
		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//获取房间号
		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//获取状态
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//将小的map插入到大的map当中.
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();
	//测试
//	for (map<int, map<string, string>>::iterator it = m_orderData.begin();
//			it != m_orderData.end(); it++)
//	{
//		cout << "条数为" << it->first << "value = ";
//		for (map<string, string>::iterator mit = it->second.begin();
//				mit != it->second.end(); mit++)
//		{
//			cout << " key=" << mit->first << " value=" << mit->second << ";";
//		}
//		cout << "\r\n";
//	}
//	cout << endl;

	//另一种打印方法:
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
		cout << "文件打开失败" << endl;
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
