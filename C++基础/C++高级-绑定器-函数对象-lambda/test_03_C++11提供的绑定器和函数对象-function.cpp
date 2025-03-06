#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;


/*
* C++11提供的绑定器和函数对象
* 绑定器，函数对象，lambda表达式 它们只能使用在一条语句中
* 
* 1、bind 函数模板
* 2、function： 类模板
* - 用函数类型实例化function；
* - 通过function调用operator()函数时，需要根据函数类型传入相应参数；
*/

/*
* function详解
*/

// function简单使用
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
public:  // 必须依赖一个对象来调用
	void hello(string str) { cout << str << endl; }
};

int main()
{
	// 从function类模板定义处，看到希望用一个函数类型实例化function
	// 注意区别函数类型和函数指针类型，如：void()  void(*)()
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


// function具体实例
#if 0
void doShowAllBooks() { cout << "查看所有书籍信息" << endl; }
void doBorrow() { cout << "借书" << endl; }
void doBack() { cout << "还书" << endl; }
void doQueryBooks() { cout << "查询书籍" << endl; }
void doLoginOut() { cout << "注销" << endl; }

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
		cout << "1.查看所有书籍信息" << endl;
		cout << "2.借书" << endl;
		cout << "3.还书" << endl;
		cout << "4.查询书籍" << endl;
		cout << "5.注销" << endl;
		cout << "------------------" << endl;
		cout << "请选择：";
		cin >> choice;

		//switch (choice)  // 不好，代码无法做到闭合，不符合"开-闭"原则
		//{
		//default:
		//	break;
		//}

		auto it = actionMap.find(choice);
		if (it == actionMap.end())
		{
			cout << "选择无效，请重新选择！" << endl;
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
* function函数对象的实现原理
* 自己实现
*/

#if 0
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }

// 自己实现function函数对象
template<typename Fty>
class myfunction {};

#if 0
template<typename R, typename A1>  // 模板部分特例化
class myfunction<R(A1)>
{
public:
	//typedef R(*PFUNC)(A1);
	using PFUNC = R(*)(A1);  // 函数指针
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

template<typename R, typename A1, typename A2>  // 模板部分特例化
class myfunction<R(A1, A2)>
{
public:
	//typedef R(*PFUNC)(A1, A2);
	using PFUNC = R(*)(A1, A2);  // 函数指针
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

// 使用可变参数实现接收多参数
template<typename R, typename... A>  // 模板部分特例化，可变参数列表
class myfunction<R(A...)>
{
public:
	//typedef R(*PFUNC)(A...);
	using PFUNC = R(*)(A...);  // 函数指针
	myfunction(PFUNC func)
		: _func(func)
	{
	}

	R operator()(A... args)  // 一组参数
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
