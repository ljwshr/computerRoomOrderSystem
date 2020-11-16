#pragma once
#include <iostream>
#include "identity.h"


class Teacher: public Identity
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);

	virtual void operMenu();

	void showAllOrder();
	void validOrder();

	int m_EmpId;

};

