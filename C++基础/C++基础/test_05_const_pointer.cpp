#include <iostream>
#include <typeinfo>

using namespace std;

/*
* 1��const��һ��ָ��Ľ��:
* C++�﷨�淶��const ���ε���������������ͣ�
* const�ұ����û��ָ��"*"�Ļ���const���������ͣ���int* const == int* �ڱ����������������ģ�
* const int* p;  ����ָ�����ⲻͬ��int���͵��ڴ棬���ǲ���ͨ��ָ�����޸�ָ����ڴ��ֵ��
* int const* p;  ͬ�ϣ�
* int* const p;  ������ָ�������ڴ棬���ǿ���ͨ��ָ��������޸�ָ����ڴ��ֵ��
* const int* const p;  ������ָ�������ڴ棬Ҳ������ͨ��ָ��������޸�ָ����ڴ��ֵ��
* 
* 2��const�Ͷ������༶��ָ��Ľ�ϣ�
* 
* const���εı����г���������ͨ������������ʲô��
* C++����������1.���뷽ʽ��ͬ��2.������Ϊ��ֵ��
* 
* const���ε��������ֵĴ���
* 1.����������Ϊ��ֵ ��= ֱ���޸ĳ�����ֵ��
* 2.���ܰѳ����ĵ�ַй¶��һ����ͨ��ָ�������ͨ�����ñ��� ��= ����޸ĳ�����ֵ;
* 
* �ܽ�const��ָ�������ת����ʽ��
* int* <- const int*  �Ǵ���ģ�
* const int* <- int*  �ǿ��Եģ�
* 
* ����ָ���£�Ҫô����const��Ҫô��û�У��������
* int** <- const int**  �Ǵ���ģ�
* const int** <- int**  �Ǵ���ģ�
* 
* (int*const*)ʵ������const��һ��ָ��Ľ��
* int** <- int* const*  �Ǵ���ģ�
* int* const* <- int**  �ǿ��Եģ�
*/

#if 0
// const��һ��ָ��Ľ��
int main01()
{
	int* q1 = nullptr;
	int* const q2 = nullptr;
	cout << typeid(q1).name() << endl;
	cout << typeid(q2).name() << endl;
	// const�ұ����û��ָ��"*"�Ļ���const�������������Σ�

	int a = 10;
	int* p1 = &a;
	const int* p2 = &a;  // const int* <- int*
	int* const p3 = &a;  // int* <- int*
	int* p4 = p3;  // int* <- int*

	//const int a = 10;
	//int* p = &a;  // *p = 30; int* <<= const int*;����;
}

// const�Ͷ���ָ��Ľ��
int main()
{
	int a = 10;
	int* p = &a;
	const int** q = &p;  // const int** <- int**������

	return 0;
}
#endif