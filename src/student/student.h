#pragma once
#include "identity.h"
class Student: public Identity
{
public:
	//Ĭ�Ϲ��캯��
	Student();
	//�вι��캯��
	Student(int id, string name, string pwd);
	//�˵�����
	virtual void operMenu();
	//����ԤԼ
	void applyOrder();
	//�鿴�ҵ�ԤԼ
	void showMyOrder();
	//�鿴���е�ԤԼ
	void showAllOrder();
	//ȡ��ԤԼ
	void cancelOrder();
	//ѧ����
	int m_Id;

private:

};
