#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;

/*
* 1、C++ STL中的绑定器（只能应用于二元函数对象，使用场景有限）
* - bind1st：把operator()的第一个形参变量绑定成一个确定的值
* - bind2nd：把operator()的第二个形参变量绑定成一个确定的值
* 本身还是一个函数对象
* 自己实现简单绑定器
*/

#if 0
template<typename Container>
void showContainer(Container& con)
{
	typename Container::iterator it = con.begin();  // 告知编译器Container::iterator是类型而不是变量
	for (;it != con.end();++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

// 绑定器底层原理
template<typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp)
{
	for (;first != last;++first)
	{
		if (comp(*first))  // comp.operator()(*first)
		{
			return first;
		}
	}

	return last;
}

template<typename Compare, typename T>
class _mybind1st  // 绑定器是函数对象的一个应用
{
public:
	_mybind1st(Compare comp, T val)
		: _comp(comp)
		, _val(val)
	{
	}

	bool operator()(const T& second)
	{
		return _comp(_val, second);  // 底层实际调用的还是二元函数对象(例如greater)
	}
private:
	Compare _comp;
	T _val;
};

template<typename Compare, typename T>
class _mybind2nd
{
public:
	_mybind2nd(Compare comp, T val)
		: _comp(comp)
		, _val(val)
	{
	}

	bool operator()(const T& first)
	{
		return _comp(first, _val);  // 底层实际调用的还是二元函数对象(例如less)
	}
private:
	Compare _comp;
	T _val;
};

// mybind1st(greater<int>(), 70)
template<typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T& val)
{
	// 直接使用函数模板，好处是可以进行类型的推演
	return _mybind1st<Compare, T>(comp, val);
}

template<typename Compare, typename T>
_mybind2nd<Compare, T> mybind2nd(Compare comp, const T& val)
{
	return _mybind2nd<Compare, T>(comp, val);
}

void test_stl_bind()
{
	vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	showContainer(vec);
	sort(vec.begin(), vec.end());  // 默认从小到大
	showContainer(vec);

	// greater 二元函数对象
	sort(vec.begin(), vec.end(), greater<int>());  // 从大到小排序
	showContainer(vec);

	/*
	* 把70按顺序插入到容器vec中，找第一个小于70的数字
	* operator()(const T& val)
	* greater a > b;
	* less a < b;
	* 绑定器 + 二元函数对象 = 一元函数对象
	* bind1st: + greater -> bool operator()(70, const _Ty& _Right)
	* bind2nd: + less -> bool operator()(const _Ty& _Left, 70)
	*/
	//auto it = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 70));
	auto it = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 70));
	if (it != vec.end())
	{
		vec.insert(it, 70);
	}

	showContainer(vec);
}

void test_custom_bind()
{
	vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	showContainer(vec);

	// greater 二元函数对象
	sort(vec.begin(), vec.end(), greater<int>());  // 从大到小排序
	showContainer(vec);

	//auto it = my_find_if(vec.begin(), vec.end(), mybind1st(greater<int>(), 70));
	auto it = my_find_if(vec.begin(), vec.end(), mybind2nd(less<int>(), 70));
	if (it != vec.end())
	{
		vec.insert(it, 70);
	}

	showContainer(vec);
}

int main()
{
	test_custom_bind();
	return 0;
}
#endif