#include <iostream>

using namespace std;

/*
* ����һ��ģ�����ȫ�������ͷ���ȫ�����֣�������
* �������ģ���ʵ�����ݣ���������ܼ򵥣�
* 
* ע�����ֺ������ͺͺ���ָ�����ͣ�
* �������ͣ�
* - typedef int PFUNC2(int, int); // �ϵ�д��
* - using PFUNC2 = int(int, int); // C++11��ʹ��using��д��
* 
* ����ָ�����ͣ�
* - typedef int(*PFUNC1)(int, int);
* - using PFUNC1 = int(*)(int, int);
*/


/*
* ģ���ʹ��
*/
#if 0
template<typename T>
bool compare(T a, T b)
{
	cout << "template compare" << endl;
	return a > b;
}

template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

int main()
{
	compare(10, 20);
	compare("aaa", "bbb");

	return 0;
}
#endif


/*
* ����һ��ģ�����ȫ�������ͷ���ȫ�����֣�������
* 
* ������ʾ
* 
*/
#if 0
template<typename T>
class Vector
{
public:
	Vector() { cout << "call Vector template init" << endl; }
};

// ���char*�����ṩ����ȫ�������汾
template<>
class Vector<char*>
{
public:
	Vector() { cout << "call Vector(char*) init" << endl; }
};

// ���ָ�������ṩ�Ĳ����������汾
template<typename Ty>
class Vector<Ty*>
{
public:
	Vector() { cout << "call Vector<Ty*> init" << endl; }
};

// ��Ժ���ָ�����ͣ��з���ֵ���������βα������ṩ�Ĳ����������汾
template<typename R, typename A1>
class Vector < R(*)(A1, A1) >
{
public:
	Vector() { cout << "Vector < R(*)(A1, A1) >" << endl; }
};

// ��Ժ������ͣ���һ������ֵ���������βα������ṩ�Ĳ����������汾
template<typename R, typename A1, typename A2>
class Vector<R(A1, A2)>
{
public:
	Vector() { cout << "Vector<R(A1, A2)>" << endl; }
};

int sum(int a, int b) { return a + b; }

int main()
{
	Vector<int> vec1;
	Vector<char*> vec2;
	Vector<int*> vec3;
	Vector<int(*)(int, int)> vec4;
	Vector<int(int, int)> vec5;

	// ����ָ������
	//typedef int(*PFUNC1)(int, int);  // ���ϵ�typedef����
	using PFUNC1 = int(*)(int, int);  // ʹ��c++11��using�ؼ��ֶ���
	PFUNC1 pfunc = sum;
	cout << pfunc(10, 29) << endl;

	// ��������
	//typedef int PFUNC2(int, int);
	using PFUNC2 = int(int, int);  // ʹ��c++11��using�ؼ���
	PFUNC2* pfunc2 = sum;
	cout << (*pfunc2)(10, 29) << endl;

	return 0;
}
#endif

/*
* �������ģ���ʵ�����ݣ���������ܼ򵥣�
* �����
* 
* 
* ������ʾ
* 
*/
#if 0
// T���������д�����ͣ�����ֵ�������β����Ͷ�ȡ����
template<typename T>
void func(T a)
{
	cout << typeid(a).name() << endl;
}

template<typename R, typename A1, typename A2>
void func2(R(*a)(A1,A2))
{
	cout << typeid(R).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}

int sum(int a, int b) { return a + b; }

class Test
{
public:
	int sum(int a, int b) { return a + b; }
};

template<typename R, typename T, typename A1, typename A2>
void func3(R(T::* a)(A1, A2))
{
	cout << typeid(R).name() << endl;
	cout << typeid(T).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}

int main()
{
	func(10);
	func("aaa");
	func(sum);  // T int(*)(int,int)
	func2(sum);
	func3(&Test::sum);
	return 0;
}
#endif
