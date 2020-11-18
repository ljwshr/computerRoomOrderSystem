
#include <map>
using namespace std;
#include "globalFile.h"

class OrderFile
{
public:
	//构造函数
	OrderFile(); // 从文件中读取相关信息
	//更新预约记录
	void updateOrder();//更新数据到文件当中
	//记录预约记录 key 记录的条款, value 具体记录的键值对信息
	map<int, map<string,string>> m_orderData;

	int m_Size;
};
