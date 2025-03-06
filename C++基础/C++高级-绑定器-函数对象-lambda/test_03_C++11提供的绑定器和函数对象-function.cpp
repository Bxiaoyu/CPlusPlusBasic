#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;


/*
* C++11�ṩ�İ����ͺ�������
* ��������������lambda���ʽ ����ֻ��ʹ����һ�������
* 
* 1��bind ����ģ��
* 2��function�� ��ģ��
* - �ú�������ʵ����function��
* - ͨ��function����operator()����ʱ����Ҫ���ݺ������ʹ�����Ӧ������
*/

/*
* function���
*/

// function��ʹ��
#if 0
void hello01()
{
	cout << "hello world!" << endl;
}

void hello02(string str)
{
	cout << str << endl;
}

int sum(int a, int b)
{
	return a + b;
}

class Test
{
public:  // ��������һ������������
	void hello(string str) { cout << str << endl; }
};

int main()
{
	// ��function��ģ�嶨�崦������ϣ����һ����������ʵ����function
	// ע�����������ͺͺ���ָ�����ͣ��磺void()  void(*)()
	function<void()> func1(hello01);
	func1();  // func1.operator()

	function<void(string)> func2 = hello02;
	func2("hello02");  // func2.operator()(string str) -> hello02(str)

	function<int(int, int)> func3 = sum;
	cout << func3(10, 20) << endl;

	function<int(int, int)> func4 = [](int a, int b)->int {return a + b;};
	cout << func4(20, 30) << endl;

	function<void(Test*, string)> func5 = &Test::hello;
	Test t;
	//func5(&Test(), "call Test::hello!");
	func5(&t, "call Test::hello!");

	return 0;
}
#endif


// function����ʵ��
#if 0
void doShowAllBooks() { cout << "�鿴�����鼮��Ϣ" << endl; }
void doBorrow() { cout << "����" << endl; }
void doBack() { cout << "����" << endl; }
void doQueryBooks() { cout << "��ѯ�鼮" << endl; }
void doLoginOut() { cout << "ע��" << endl; }

int main()
{
	map<int, function<void()>> actionMap;
	actionMap.insert({ 1, doShowAllBooks });
	actionMap.insert({ 2, doBorrow });
	actionMap.insert({ 3, doBack });
	actionMap.insert({ 4, doQueryBooks });
	actionMap.insert({ 5, doLoginOut });

	int choice = 0;
	for (;;)
	{
		cout << "------------------" << endl;
		cout << "1.�鿴�����鼮��Ϣ" << endl;
		cout << "2.����" << endl;
		cout << "3.����" << endl;
		cout << "4.��ѯ�鼮" << endl;
		cout << "5.ע��" << endl;
		cout << "------------------" << endl;
		cout << "��ѡ��";
		cin >> choice;

		//switch (choice)  // ���ã������޷������պϣ�������"��-��"ԭ��
		//{
		//default:
		//	break;
		//}

		auto it = actionMap.find(choice);
		if (it == actionMap.end())
		{
			cout << "ѡ����Ч��������ѡ��" << endl;
		}
		else
		{
			it->second();
		}
	}

	return 0;
}
#endif

/*
* function���������ʵ��ԭ��
* �Լ�ʵ��
*/

#if 0
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }

// �Լ�ʵ��function��������
template<typename Fty>
class myfunction {};

#if 0
template<typename R, typename A1>  // ģ�岿��������
class myfunction<R(A1)>
{
public:
	//typedef R(*PFUNC)(A1);
	using PFUNC = R(*)(A1);  // ����ָ��
	myfunction(PFUNC func)
		: _func(func)
	{
	}

	R operator()(A1 arg)
	{
		return _func(arg);  // hello(arg)
	}
private:
	PFUNC _func;
};

template<typename R, typename A1, typename A2>  // ģ�岿��������
class myfunction<R(A1, A2)>
{
public:
	//typedef R(*PFUNC)(A1, A2);
	using PFUNC = R(*)(A1, A2);  // ����ָ��
	myfunction(PFUNC func)
		: _func(func)
	{
	}

	R operator()(A1 arg1, A2 arg2)
	{
		return _func(arg1, arg2);  // hello(arg)
	}
private:
	PFUNC _func;
};
#endif

// ʹ�ÿɱ����ʵ�ֽ��ն����
template<typename R, typename... A>  // ģ�岿�����������ɱ�����б�
class myfunction<R(A...)>
{
public:
	//typedef R(*PFUNC)(A...);
	using PFUNC = R(*)(A...);  // ����ָ��
	myfunction(PFUNC func)
		: _func(func)
	{
	}

	R operator()(A... args)  // һ�����
	{
		return _func(args...);  // hello(arg)
	}
private:
	PFUNC _func;
};

int main()
{
	myfunction<void(string)> func1(hello);
	func1("Hello!");  // func1.operator()("Hello!")

	myfunction<int(int, int)> func2(sum);
	cout << func2(10, 20) << endl;

	return 0;
}
#endif
