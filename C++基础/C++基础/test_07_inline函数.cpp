#include <iostream>
#include <typeinfo>

using namespace std;

/*
* inline�������� �� ��ͨ���������𣿣�
* 1.inline���������ڱ�������У�û�к������ÿ������ں����ĵ��õ�Ѻ����Ĵ������չ�������ˣ�
* 2.inline��������������Ӧ�ĺ������ţ�
* 
* inlineֻ�ǽ������������������������������
* ���������е�inline���ᱻ�������������������������ݹ麯����
* 
* debug�汾�£�inline�ǲ������õģ�ֻ����release�汾�������ã�
* 
* inline�ʺ��ڼ򵥺�����
*/

#if 0
inline int sum(int a, int b = 20)  // ��������������sum_int_int��������
{
	return a + b;
}

int sum2(int a, int b)  // sum2_int_int
{
	return a + b;
}

int main()
{
	int a = 30;
	int b = 40;

	int ret = sum(a, b);  // ֱ��չ����a+b�����˺������ÿ���
	cout << "ret:" << ret << endl;

	ret = sum2(a, b);
	// �˴��к����ı�׼���ù��� ����ѹջ������ջ֡�Ŀ��ٺͻ��˹���
	// �к������õĿ���
	// a+b mov add mov 1000000 a+b
	cout << "ret:" << ret << endl;

	return 0;
}
#endif