
#include <map>
using namespace std;
#include "globalFile.h"

class OrderFile
{
public:
	//���캯��
	OrderFile(); // ���ļ��ж�ȡ�����Ϣ
	//����ԤԼ��¼
	void updateOrder();//�������ݵ��ļ�����
	//��¼ԤԼ��¼ key ��¼������, value �����¼�ļ�ֵ����Ϣ
	map<int, map<string,string>> m_orderData;

	int m_Size;
};
