#include <iostream>
#include <typeinfo>

using namespace std;

/*
* �βδ�Ĭ��ֵ�ĺ���
* 1.��Ĭ��ֵ��ʱ�򣬴����������
* 2.����Ч�ʵ����⣻
* 3.�������崦���Ը��β�Ĭ��ֵ��������Ҳ���Ը��β�Ĭ��ֵ��
* 4.�βθ�Ĭ��ֵ��ʱ�򣬲����Ƕ��崦�����������������β�Ĭ��ֵֻ�ܳ���һ�Σ�
*/

#if 0
int sum(int a, int b = 20);  // ����ʱ�������Ĭ��ֵ

int sum(int a=10, int b = 20)  // ���崦������Ĭ��ֵ
{
	return a + b;
}

int main()
{
	int a = 30;
	int b = 40;

	int ret = sum(a, b);
	cout << "ret:" << ret << endl;

	ret = sum(a);
	cout << "ret:" << ret << endl;

	ret = sum();
	cout << "ret:" << ret << endl;
}

#endif