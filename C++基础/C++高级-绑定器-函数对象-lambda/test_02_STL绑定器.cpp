#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;

/*
* 1��C++ STL�еİ�����ֻ��Ӧ���ڶ�Ԫ��������ʹ�ó������ޣ�
* - bind1st����operator()�ĵ�һ���βα����󶨳�һ��ȷ����ֵ
* - bind2nd����operator()�ĵڶ����βα����󶨳�һ��ȷ����ֵ
* ������һ����������
* �Լ�ʵ�ּ򵥰���
*/

#if 0
template<typename Container>
void showContainer(Container& con)
{
	typename Container::iterator it = con.begin();  // ��֪������Container::iterator�����Ͷ����Ǳ���
	for (;it != con.end();++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

// �����ײ�ԭ��
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
class _mybind1st  // �����Ǻ��������һ��Ӧ��
{
public:
	_mybind1st(Compare comp, T val)
		: _comp(comp)
		, _val(val)
	{
	}

	bool operator()(const T& second)
	{
		return _comp(_val, second);  // �ײ�ʵ�ʵ��õĻ��Ƕ�Ԫ��������(����greater)
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
		return _comp(first, _val);  // �ײ�ʵ�ʵ��õĻ��Ƕ�Ԫ��������(����less)
	}
private:
	Compare _comp;
	T _val;
};

// mybind1st(greater<int>(), 70)
template<typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T& val)
{
	// ֱ��ʹ�ú���ģ�壬�ô��ǿ��Խ������͵�����
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
	sort(vec.begin(), vec.end());  // Ĭ�ϴ�С����
	showContainer(vec);

	// greater ��Ԫ��������
	sort(vec.begin(), vec.end(), greater<int>());  // �Ӵ�С����
	showContainer(vec);

	/*
	* ��70��˳����뵽����vec�У��ҵ�һ��С��70������
	* operator()(const T& val)
	* greater a > b;
	* less a < b;
	* ���� + ��Ԫ�������� = һԪ��������
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

	// greater ��Ԫ��������
	sort(vec.begin(), vec.end(), greater<int>());  // �Ӵ�С����
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