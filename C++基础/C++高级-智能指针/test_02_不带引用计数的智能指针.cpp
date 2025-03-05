#include <iostream>
#include <memory>

using namespace std;

/*
* �������ü���������ָ�룬��ν��ǳ�������⣿
* auto_ptr:C++������ģ����Ƽ�ʹ�ã�ǳ���������������
*
* C++11�±�׼��
* 1��scoped_ptr����֧�ֿ�������Ϳ�����ֵ�����ܽ��к������κͷ��صȣ�ʹ�ñȽ���
* - scoped_ptr(const scoped_ptr<T>&) = delete;
* - scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;
*
* 2��unique_ptr���Ƽ�ʹ��
* Ҳ��֧����ͨ��������Ϳ������������
* - unique_ptr(const unique_ptr<T>&) = delete;
* - unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
*
* �����ṩ�˴���ֵ���ò����Ŀ�������Ϳ������������
* - unique_ptr(unique_ptr<T>&&);
* - unique_ptr<T>& operator=(unique_ptr<T>&&);
*/

#if 0
int main()
{
	//auto_ptr<int> ptr1(new int);
	//auto_ptr<int> ptr2(ptr1);
	//*ptr2 = 20;  // ����
	//cout << *ptr1 << endl;

	unique_ptr<int> ptr1(new int);
	// std::move -> c++11 ��ֵ���� std::move�õ���ǰ��������ֵ����
	unique_ptr<int> ptr2(std::move(ptr1));
	return 0;
}
#endif