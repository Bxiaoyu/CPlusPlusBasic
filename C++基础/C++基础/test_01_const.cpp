#include <iostream>
#include <typeinfo>

using namespace std;

#if 0
int main()
{
	/*
	* C��C++��const��������ʲô��
	*	C++��const�����ʼ�����г�����
	*	C��const���Բ���ʼ�����г�����;
	* const�ı��뷽ʽ��ͬ��
	*	C�У�const�ǵ���һ����������������ָ��
	*	C++�У����г���const�������ֵĵط������������ĳ�ʼ���滻��
	*/
	int b = 20;
	//const int a = b;  // ������
	const int a = 20; // ����
	int array[a] = {};
	int* p = (int*) & a;
	*p = 30;

	printf("%d %d %d \n", a, *p, *(&a));
	return 0;
}
#endif