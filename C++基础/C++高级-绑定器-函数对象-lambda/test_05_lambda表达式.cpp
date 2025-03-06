#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

/*
* lambda����������������汾
* 
* ��������ȱ�㣺
* ��Ҫʹ���ڷ����㷨�Ĳ������ݣ��Ƚ�����/�Զ�����������ȼ����У�����ָ�룩
* 
* lambda���ʽ���﷨��
* 1.[�����ⲿ����](�β��б�)->����ֵ����{��������}
* 2.���lambda���ʽ�ķ���ֵ����Ҫ����ô"->����ֵ"����ʡ��
* 
* [�����ⲿ����]:
* - []����ʾ�������κ��ⲿ����
* - [=]����ֵ���ݵķ�ʽ�����ⲿ���б���
* - [&]�������ô��ݵķ�ʽ�����ⲿ���б���
* - [this]�������ⲿ��thisָ��
* - [=, &a]����ֵ���ݵķ�ʽ�����ⲿ���б���������a�����Դ����÷�ʽ����
* - [a, b]����ֵ���ݵķ�ʽ�����ⲿ����a��b
* - [a, &b]��a��ֵ���ݲ���b�Դ����÷�ʽ����
*/

/*
* lambdaԭ�����
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

	// 65����������У�Ҫ�ҵ�һ��С��65������
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
	auto func3 = [&]()  // ��ֵ������Ҫ�ı�ԭ���ݵĻ���������Ҫ��mutable
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
* lambda���ʽֻ��ʹ������䵱�У����������ʹ��֮ǰ����õ�lambda���ʽ����ô���أ�
* ��ʲô��������ʾlambda���ʽ�أ�
* - ��Ȼ����function��������ʾ��������������
* 
* lambda -> ��������
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
	// ����ָ���Զ���ɾ���� delete p;
	unique_ptr<FILE, function<void(FILE*)>> ptr(fopen("data.txt", "w"), [](FILE* pf)
		{
			cout << "file closed!" << endl;
			fclose(pf);
		});

	// ���ȼ�����
	//priority_queue<Data> que;  // ���ȼ�������Ҫ֧�ֱȽ�
	using FUNC = function<bool(Data&, Data&)>;
	priority_queue<Data, vector<Data>, FUNC> maxHeap(
		[](Data& d1, Data& d2)->bool
		{
			return d1.ma > d2.ma;
		}
	);  // �����
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