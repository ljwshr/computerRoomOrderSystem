#pragma once
#include <iostream>
#include <string>

using namespace std;

//��ݳ�����
class Identity
{
public:
	//�����˵�,���麯��
	//ÿ�����඼���Լ������Ĳ����˵�. �Լ�ȥ����ʵ��.
	virtual void operMenu()=0;
	string m_Name;
	string m_Pwd;
};
