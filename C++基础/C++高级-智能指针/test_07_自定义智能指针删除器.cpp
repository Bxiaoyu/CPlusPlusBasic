#include <iostream>
#include <memory>
#include <functional>

using namespace std;

/*
* ����ָ���ɾ���� deletor
* ����ָ�룺�ܹ�ȷ����Դ�ľ����ͷ� delete ptr��
* 
~unique_ptr() { ��һ����������ĵ��� deletor(ptr); }
template<typename T>
class Deletor
{
public:
	void operator()(T* ptr)
	{
		delete ptr;
	}
};
*/

#if 0
// �Զ��庯������ɾ����
template<typename T>
class MyDeletor
{
public:
	void operator()(T* ptr) const
	{
		cout << "call MyDeletor.operator()" << endl;
		delete[] ptr;
	}
};

template<typename T>
class MyFileDeletor
{
public:
	void operator()(T* ptr) const
	{
		cout << "call MyFileDeletor.operator()" << endl;
		fclose(ptr);
	}
};


int main()
{
	unique_ptr<int, MyDeletor<int>> ptr1(new int[100]);
	unique_ptr<FILE, MyFileDeletor<FILE>> ptr2(fopen("data.txt", "w"));

	// ʹ��lambda���ʽ���򻯴���
	// lambda -> �������� function
	unique_ptr<int, function<void(int*)>> ptr3(new int[100],
		[](int* p)->void
		{
			cout << "call lambda release new int[100]" << endl;
			delete[] p;
		});

	unique_ptr<FILE, function<void(FILE*)>> ptr4(fopen("data.txt", "w"),
		[](FILE* p)->void
		{
			cout << "call lambda release fopen()" << endl;
			fclose(p);
		});

	shared_ptr<int> ptr5(new int[10],
		[](int* p)->void
		{
			cout << "call lambda release new int[10]" << endl;
			delete[] p;
		});

	return 0;
}
#endif