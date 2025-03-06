#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

/*
* lambda：函数对象的升级版本
* 
* 函数对象缺点：
* 主要使用在泛型算法的参数传递（比较性质/自定义操作，优先级队列，智能指针）
* 
* lambda表达式的语法：
* 1.[捕获外部变量](形参列表)->返回值类型{操作代码}
* 2.如果lambda表达式的返回值不需要，那么"->返回值"可以省略
* 
* [捕获外部变量]:
* - []：表示不捕获任何外部变量
* - [=]：以值传递的方式捕获外部所有变量
* - [&]：以引用传递的方式捕获外部所有变量
* - [this]：捕获外部的this指针
* - [=, &a]：以值传递的方式捕获外部所有变量，但是a变量以传引用方式捕获
* - [a, b]：以值传递的方式捕获外部变量a和b
* - [a, &b]：a以值传递捕获，b以传引用方式捕获
*/

/*
* lambda原理解析
*/
#if 0
template<typename T=void>
class TestLambda01
{
public:
	TestLambda01() {}
	void operator()() const
	{
		cout << "Hello world!" << endl;
	}
};

template<typename T = int>
class TestLambda02
{
public:
	TestLambda02() {}
	T operator()(T a, T b) const
	{
		return a + b;
	}
};

template<typename T = int>
class TestLambda03
{
public:
	TestLambda03(T& a, T& b):ma(a),mb(b) {}
	void operator()() const
	{
		T tmp = ma;
		ma = mb;
		mb = tmp;
	}
private:
	T& ma;
	T& mb;
};

int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	sort(vec.begin(), vec.end(), [](int a, int b)->bool
		{
			return a > b;
		});

	for (auto val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	// 65按序插入序列，要找第一个小于65的数字
	auto it = find_if(vec.begin(), vec.end(), [](int a)->bool
		{
			return a < 65;
		});

	if (it != vec.end())
	{
		vec.insert(it, 65);
	}

	for (auto val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	for_each(vec.begin(), vec.end(), [](int a)
		{
			cout << a << " ";
		});
	cout << endl;

#if 0
	auto func1 = []()->void {cout << "Hello world!" << endl;};
	func1();

	auto func2 = [](int a, int b)->int {return a + b;};
	cout << func2(10, 20) << endl;

	int a = 20;
	int b = 30;
	auto func3 = [&]()  // 按值传递需要改变原数据的话（）后需要加mutable
		{
			int tmp = a;
			a = b;
			b = tmp;
		};
	func3();
	cout << "a:" << a << " b:" << b << endl;


	TestLambda01<> t1;
	t1();

	TestLambda02<int> t2;
	cout << t2(10, 20) << endl;

	TestLambda03<int> t3(a, b);
	t3();
	cout << "a:" << a << " b:" << b << endl;
#endif
	return 0;
}
#endif

/*
* lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，怎么办呢？
* 用什么类型来表示lambda表达式呢？
* - 当然是用function类型来表示函数对象类型了
* 
* lambda -> 函数对象
*/
#if 0
class Data
{
public:
	Data(int val1, int val2)
		: ma(val1)
		, mb(val2)
	{
	}

	//bool operator>(const Data& obj) const { return ma > obj.ma; }
	//bool operator<(const Data& obj) const { return ma < obj.ma; }

public:
	int ma;
	int mb;
};

int main()
{
	// 智能指针自定义删除器 delete p;
	unique_ptr<FILE, function<void(FILE*)>> ptr(fopen("data.txt", "w"), [](FILE* pf)
		{
			cout << "file closed!" << endl;
			fclose(pf);
		});

	// 优先级队列
	//priority_queue<Data> que;  // 优先级队列需要支持比较
	using FUNC = function<bool(Data&, Data&)>;
	priority_queue<Data, vector<Data>, FUNC> maxHeap(
		[](Data& d1, Data& d2)->bool
		{
			return d1.ma > d2.ma;
		}
	);  // 大根堆
	maxHeap.push(Data(10, 20));
	maxHeap.push(Data(15, 15));
	maxHeap.push(Data(20, 10));

#if 0
	map<int, function<int(int, int)>> calculateMap;
	calculateMap[1] = [](int a, int b)->int {return a + b;};
	calculateMap[2] = [](int a, int b)->int {return a - b;};
	calculateMap[3] = [](int a, int b)->int {return a * b;};
	calculateMap[4] = [](int a, int b)->int {return a / b;};

	cout << "10 + 15 = " << calculateMap[1](10, 25) << endl;
#endif

	return 0;
}
#endif