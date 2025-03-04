#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>  // ����STL�����㷨
#include <functional>  // ������������Ͱ���

using namespace std;

/*
* C++ STL standard template libaray ��׼ģ���
* һ����׼���� C++11 array forward_list
* �����У�����Ĺ����������ڴ�Ŀ����ͷţ������ɿռ���������allocator����ʵ�ֵģ����������ĸ�������
* allocate   ����ռ�
* deallocate �ͷſռ�
* construct  �������
* destroy    ��������
* 
* 1.˳������
* vector ��̬���ٵ����飬ÿ����ԭ���ռ��С��2����������
* deque
* list
* 
* 2.����������
* stack
* queue
* priority_queue
* 
* 3.��������
* ����������� -> ������ʽ��ϣ�� ��ɾ��O(1)
* unordered_set
* unordered_multiset
* unordered_map
* unordered_multimap
* 
* ����������� -> ���ں���� ��ɾ��O(log2n) 2�ǵ��������Ĳ��������ĸ߶ȣ�
* set
* multiset
* map
* multimap
* 
* ע�⣺mapϵ�е�operator[]�������ţ��������������ܣ�
* 1.��ѯ��
* 2.���key�����ڣ��������һ������[key,v()]
* 
* ����������
* ���飬string��bitset��λ������
* 
* ����������
* iterator��const_iterator
* reverse_iterator��const_reverse_iterator
* 
* �ġ�������������C�ĺ���ָ�룩
* greater��less
* 
* �塢�����㷨���ܶ࣬��������ܼ������õģ�
* sort��find��find_if��binary_search��for_each
*/

/*
* vector����������
* �ײ����ݽṹ����̬���ٵ����飬ÿ����ԭ���ռ��С��2����������
* 
* vector<int> vec;
* ���ӣ�
* vec.push_back(20); ĩβ���Ԫ��O(1) �ᵼ����������
* vec.insert(it, 20); it������ָ���λ�����һ��Ԫ��20 O(N) �ᵼ����������
* 
* ɾ����
* vec.pop_back(); ɾ��ĩβԪ�� O(1)
* vec.erase(it);  ɾ��������ָ���Ԫ�� O(N)
* 
* ��ѯ��
* operator[] �±���������vec[5] O(1)
* iterator���������б���
* find��for_each
* foreach -> �ײ�ͨ��iterator��ʵ�ֵ�
* 
* ע�⣺���������������������ɾ��������insert/erase����һ��Ҫ���µ������������һ��insert����erase��ɺ󣬵�������ʧЧ�ˡ�
* 
* ���÷������ܣ�
* size()
* empty()
* reserve(20); vectorԤ���ռ�ģ�ֻ�������ײ㿪��ָ����С���ڴ�ռ䣬�����������Ԫ��
* resize(20);  ���������õģ������������ײ㿪��ָ����С���ڴ�ռ䣬���������Ԫ��
* swap(); ������������Ԫ����
*/
#if 0
int main()
{
	vector<int> vec;
	//vec.reserve(20);  // vector����Ԥ���ռ� ���Լ���Ƶ�����ݴ���
	vec.resize(20);  // ���ٿռ䲢��ʼ��Ԫ��Ϊ0
	cout << vec.empty() << endl;
	cout << vec.size() << endl;

	for (int i = 0; i < 20; ++i)
		vec.push_back(rand() % 100 + 1);

	cout << vec.empty() << endl;
	cout << vec.size() << endl;

#if 0
	int size = vec.size();
	for (int i = 0; i < size; ++i)
		cout << vec[i] << " ";
	cout << endl;

	// ������������ż��ɾ��
	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			it = vec.erase(it);  // ע����µ�����
		}
		else
		{
			++it;
		}
	}

	// ͨ����������������
	auto it2 = vec.begin();
	for (;it2 != vec.end(); ++it2)
		cout << *it2 << " ";
	cout << endl;

	// ��vector����������ż��ǰ�����һ��С������1��ż�� 44 45
	for (it2 = vec.begin(); it2 != vec.end(); ++it2)
	{
		if (*it2 % 2 != 0)
		{
			it2 = vec.insert(it2, *it2 - 1);
			++it2;
		}
	}

	for (auto& val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
#endif

	return 0;
}
#endif


/*
* һ��deque��˫�˶�������
* �ײ����ݽṹ����̬���ٵĶ�ά���飬һά�����2��ʼ����2���ķ�ʽ�������ݣ�ÿ�����ݺ�ԭ���ڶ�ά�����飬���µĵ�һά�����
* �±� oldsize/2 ��ʼ��ţ����¶�Ԥ����ͬ�Ŀ��У�����֧��deque����βԪ����ӡ�
* 
* deque<int> deq;
* ���ӣ�
* deq.push_back(20); ��β�����Ԫ�� O(1)
* deq.push_front(20); ��ͷ�����Ԫ�� O(1)
* deq.insert(it, 20); itָ���λ�����Ԫ�� O(N)
* 
* ɾ����
* deq.pop_back(); ��ĩβɾ��Ԫ�� O(1)
* deq.pop_front(); ��ͷ��ɾ��Ԫ�� O(1)
* deq.erase(it); ��itָ���λ��ɾ��Ԫ�� O(N)
* 
* ��ѯ������
* iterator��������insert��eraseһ��Ҫ���ǵ�����ʧЧ���⣩
* 
* ����list����������
* �ײ����ݽṹ��˫���ѭ������ pre data next
* 
* list<int> mylist;
* ���ӣ�
* mylist.push_back(20); ��ĩβ���Ԫ�� O(1)
* mylist.push_front(20); ���ײ����Ԫ�� O(1)
* mylist.insert(it, 20); it ָ���λ�����Ԫ�� O(1)
* �����н���insert����ʱ����Ҫ����query��ѯ��������������˵����ѯ����Ч�ʱȽ���
* 
* ɾ����
* mylist.pop_back(); ��β��ɾ��Ԫ�� O(1)
* mylist.pop_front(); ���ײ�ɾ��Ԫ�� O(1)
* mylist.erase(it);  ��itָ����λ��ɾ��Ԫ�� O(1)
* 
* ��ѯ������
* iterator��������insert��eraseһ��Ҫ���ǵ�����ʧЧ���⣩
* 
* ����vector��deque��list�Ƚϣ�
* vector�ص㣺��̬���飬�ڴ��������ģ�2���ķ�ʽ�������ݣ�
* deque�ص㣺��̬���ٵĶ�ά����ռ䣬�ڶ�ά�ǹ̶����ȵ�����ռ䣬���ݵ�ʱ�򣨵�һά���������2�����ݣ���
* �澭���⣺deque�ײ��ڴ��Ƿ������������ǣ�ÿһ���ڶ�ά����������
* 
* 
* ���������򿼲죺�������յ����
* �����ĺ��򿼲죺��������֮��ĶԱ�
* 
* vector��deque֮�������
* 1.�ײ����ݽṹ����
* 2.ǰ�к����ɾ��Ԫ�ص�ʱ�临�Ӷȣ��м��ĩβ����O(1)��ǰ deque O(1)��vector O(N)��
* 3.�����ڴ��ʹ��Ч�ʣ�vector��Ҫ���ڴ�ռ�����������ģ�deque���Էֿ�������ݴ洢���ڴ�ռ䲻���������ģ�
* 4.���м����insert��erase��vector��deque�ĸ�Ч�ʸ���һ���أ���Ȼʱ�临�Ӷȶ���O(N)����������vector�������ڴ棬����vector����һ�㣻
* 
* vector��list֮�������
* 1.�ײ����ݽṹ����
	- ���飺���ӣ�ɾ������ѯO(n)���������O(1)
	- ˫��ѭ���б����ӣ�ɾ��O(1)��Ҫ��������ʱ�䣩
*/


/*
* һ����׼����-���������� -> ���������ģʽ�е�������ģʽ
* 1����������������
* a.�������ײ�û���Լ������ݽṹ�����Ƕ���һ�������ķ�װ�����ķ���ȫ���ɵײ���������������ʵ�֣�
* b.������û��ʵ���Լ��ĵ�������
* 
* template<typename T, typename Container=deque<T>>
* class Stack
* {
* public:
*	void push(const T& val) { con.push_back(val); }
*	void pop() { con.pop_back(); }
*	T top() const { return con.back(); }
* private:
*	Container con;
* };
* 
* 
* stack��push��ջ pop��ջ topջ��Ԫ�� empty�п� sizeԪ�ظ�����
* queue��push��� pop���� front��ͷԪ�� back��βԪ�� empty�п� sizeԪ�ظ�����
* priority_queue��push��� pop���� top��ͷԪ�� empty�п� sizeԪ�ظ�����Ĭ�ϴ���ѽṹ��
* 
* 2��Ϊʲô stack �� queue �ײ���������deque������vector��
* a.vector�ĳ�ʼ�ڴ�ʹ��Ч��̫�ͣ�û��deque�ã�vector 0-1-2-3-4 deque 4096��
* b.����queue��˵����Ҫ֧��β�����룬ͷ��ɾ����O(1)������vector�Ļ��ײ����Ч�ʺܵͣ�
* c.vector��Ҫ��Ƭ�����ڴ棬dequeֻ��Ҫ�ֶε��ڴ棬���洢��������ʱ����Ȼdeque���ڴ������ʸ���һЩ��
* 
* 3��Ϊʲô priority_queue �ײ���������vector������deque��
* a.priority_queue�ײ�Ĭ�ϰ��������һ������ѽṹ�����ݷ��ʿ��±����㣩����һ���ڴ������������Ϲ���һ��
*   ����ѻ���С���ѣ�
* b.deque�ڴ沢����������Щ���������㣻
*/

#if 0
int main()
{
	stack<int> s;
	queue<int> q;
	priority_queue<int> pq;
	for (int i = 0; i < 20; ++i)
	{
		s.push(i + 1);
		q.push(i + 1);
		pq.push(i + 1);
	}

	cout << "stack:" << endl;
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

	cout << "queue:" << endl;
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;

	cout << "priority_queue:" << endl;
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;

	return 0;
}
#endif

/*
* �����������
* set  Ԫ�ز��ظ�
* multiset  Ԫ�ؿ����ظ�
* map  Ԫ�ز��ظ�
* multimap  Ԫ�ؿ����ظ�
* 
* ע�⣺�Զ�����������ʹ�������������set��ʱ����Ҫ�����������ṩС��<����������غ�����
* bool operator<(const T& obj) const;
*/

#if 0
#define USE_SET 0
// ѧ����
class Student
{
public:
	Student(int id, string name) 
		: id_(id)
		, name_(name)
	{}

	// �ṩ<��������أ��Ա������������������ʹ��
#if USE_SET
	bool operator<(const Student& stu) const
	{
		return this->id_ < stu.id_;
	}
#endif
private:
	int id_;
	string name_;
	friend ostream& operator<<(ostream& out, const Student& stu);
};

ostream& operator<<(ostream& out, const Student& stu)
{
	out << "id:" << stu.id_ << " name:" << stu.name_ << endl;
	return out;
}

int main()
{
	map<int, Student> stuMap;
	stuMap.insert({ 1000, Student(1000, "����") });
	stuMap.insert({ 1002, Student(1002, "����") });
	stuMap.insert({ 1001, Student(1001, "����") });

	for (const auto& item : stuMap)
	{
		cout << item.second << endl;
	}

#if 0
	set<Student> st;
	st.insert(Student(1020, "����"));
	st.insert(Student(1001, "����"));
	st.insert(Student(1002, "����"));
	st.insert(Student(1003, "����"));

	for (const auto& val : st)
	{
		cout << val << endl;
	}
#endif
	/*
	set<int> s;
	for (int i = 0; i < 20; ++i)
	{
		s.insert(rand() % 20 + 1);
	}

	for (auto val : s)
	{
		cout << val << " ";
	}
	cout << endl;
	*/

	return 0;
}

#endif

/*
* �����������
* ���������ײ�����ݽṹ O(1)��O(log2n)
* unordered_set
* unordered_multiset
* unordered_map
* unordered_multimap
* 
* ������ɾ�Ĳ鷽����
* ���ӣ�insert(val)
* ������iterator
* ���ң�find
* ɾ����erase(key)��erase(it)
*/
#if 0
int main()
{
	// ���������ݲ��ظ���ȥ�ظ�
	const int ARR_LEN = 100000;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i)
	{
		arr[i] = rand() % 10000 + 1;
	}

	// �����10��������У������ݽ���ȥ��
	unordered_set<int> s1;
	for (const auto& v : arr)
	{
		s1.insert(v);
	}

	for (const auto& v : s1)
	{
		cout << v << endl;
	}

#if 0
	// �����10��������У�ͳ����Щ�����ظ��ˣ������ظ��˼���
	unordered_map<int, int> map1;
	for (auto& k : arr)
	{
		auto it = map1.find(k);
		if (it == map1.end())
		{
			map1.insert({ k, 1 });
		}
		else
		{
			it->second++;
		}

		//map1[k]++; Ҳ��������map�Ĳ������ʼ򻯴��룬��map[k]û��ѯ��Ԫ�صĻ����Զ�����һ��
	}

	for (const auto& p : map1)
	{
		if (p.second > 1)
		{
			cout << "key:" << p.first << " count:" << p.second << endl;
		}
	}
#endif
	return 0;
}
#endif


/*
* �����ĵ�����iterator
* iterator����ͨ��������� begin(),end()
* const_iterator����������������� ֻ�ܶ�������д
* 
* reverse_iterator����ͨ�����������rbegin(),rend()
* const_reverse_iterator�������ķ�������� ֻ�ܶ�������д
*/
#if 0
int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100);
	}

	/*
	class const_iterator
	{
	public:
		const T& operator*() { return *ptr_; }
	};

	class iterator : public const_iterator
	{
	public:
		T& operator*() { return *ptr_; }
	};
	*/

	//auto it1 = vec.begin();
	vector<int>::const_iterator it1 = vec.begin();
	for (;it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
		//if (*it1 % 2 == 0)
		//{
		//	//*it1 = 0;  // const_iterator�²����޸�
		//}
	}
	cout << endl;

	// rbegin()�����ص������һ��Ԫ�صķ����������ʾ
	// rend()�����ص�����Ԫ��ǰ��λ�õĵ�������ʾ
	vector<int>::reverse_iterator rit = vec.rbegin();
	for (;rit != vec.rend();++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;

	for (auto& val : vec)
	{
		cout << val << " ";
	}
	cout << endl;
}
#endif


/*
* �������� -��C������ĺ���ָ��
* 1��ͨ�������������operator()������ʡ�Ժ����ĵ��ÿ�������ͨ������ָ����ú��������ܹ�inline�������ã�Ч�ʸߣ�
* 2����Ϊ�����������������ɵģ����Կ��������صĳ�Ա������������¼��������ʹ��ʱ�������Ϣ��
*/

#if 0
// ʹ��C�ĺ���ָ��������
template<typename T>
bool myGreater(T a, T b)
{
	return a > b;
}

template<typename T>
bool myLess(T a, T b)
{
	return a < b;
}

// ʹ��C++��������������
template<typename T>
class Greater
{
public:
	bool operator()(T a, T b)  // ��Ԫ��������
	{
		return a > b;
	}
};

template<typename T>
class Less
{
public:
	bool operator()(T a, T b)  // ��Ԫ��������
	{
		return a < b;
	}
};

// compare��C++�Ŀ⺯��ģ��
template<typename T, typename Compare>
bool compare(T a, T b, Compare comp)
{
	// 1.ͨ������ָ����ú�������û�а취�����ģ��������ڱ���׶β�֪�����庯����˭��Ч�ʺܵͣ���Ϊ�к������ÿ���
	// 2.ͨ�����������ǿ��������ģ�ʡ�Ե��ÿ��� operator()(a,b)
	return comp(a, b);
}

int main()
{
	cout << compare(10, 20, myGreater<int>) << endl;  // ����ָ��
	cout << compare(10, 20, myLess<int>) << endl;
	cout << compare(10, 20, Greater<int>()) << endl;  // ��������
	cout << compare(10, 20, Less<int>()) << endl;

	// ���ȼ�����
	priority_queue<int> que1;  // Ĭ�ϴ����
	using MinHeap = priority_queue<int, vector<int>, greater<int>>;  // ʹ��С����
	MinHeap que2;
	for (int i = 0; i < 20; ++i)
	{
		auto tmp = rand() % 100;
		que1.push(tmp);
		que2.push(tmp);
	}

	while (!que1.empty())
	{
		cout << que1.top() << " ";
		que1.pop();
	}
	cout << endl;

	while (!que2.empty())
	{
		cout << que2.top() << " ";
		que2.pop();
	}
	cout << endl;

	// ����
	set<int> s1;  // Ĭ�ϴ�С��������
	set<int, greater<int>> s2;  // ѡ��Ӵ�С����
	for (int i = 0; i < 20; ++i)
	{
		auto tmp = rand() % 100;
		s1.insert(tmp);
		s2.insert(tmp);
	}

	for (auto& val : s1)
	{
		cout << val << " ";
	}
	cout << endl;

	for (auto& val : s2)
	{
		cout << val << " ";
	}
	cout << endl;

	return 0;
}
#endif

/*
* �����㷨 = template + ������ + ��������
* �ص㣺
* 1.�����㷨�Ĳ������յĶ��ǵ�������
* 2.�����㷨�Ĳ��������Խ��պ�������C����ָ�룩��
* sort��find��find_if��binary_search��for_each
* 
* ���� + ��Ԫ�������� -��һԪ��������
* bind1st���Ѷ�Ԫ���������operator()�ĵ�һ���βΰ�����
* bind2nd���Ѷ�Ԫ���������operator()�ĵڶ����βΰ�����
*/
#if 0
int main()
{
	int arr[] = { 12, 4, 78, 98, 21, 10, 9, 56, 63 };
	cout << sizeof(arr) << endl;
	cout << sizeof(arr) / sizeof(arr[0]) << endl;
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	sort(vec.begin(), vec.end());  // Ĭ��С��������
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	if (binary_search(vec.begin(), vec.end(), 21))  // ���������н��ж��ֲ���
	{
		cout << "binary_search:21����" << endl;
	}
	
	auto it = find(vec.begin(), vec.end(), 21);  // ʱ�临�Ӷȱ�binary_search��
	if (it != vec.end())
	{
		cout << "find:21����" << endl;
	}

	// ���뺯������greater���ı�����Ԫ������ʱ�ıȽϷ�ʽ
	sort(vec.begin(), vec.end(), greater<int>());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	/*
	* 98 78 63 56 21 12 10 9 4
	* ��48������뵽vector�������У��ҵ�һ��С��48������
	* find_if��Ҫ����һ��һԪ��������
	* greater a > b less a < b
	* 
	*/
	//auto it1 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 48));
	//auto it1 = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 48));  // Ч��ͬ��
	auto it1 = find_if(vec.begin(), vec.end(), [](int val)->bool {return val < 48;});  // Ч��ͬ��
	vec.insert(it1, 48);
	for (auto& val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	// for_each��ӡż��
	for_each(vec.begin(), vec.end(), [](int val)->void {
		if (val % 2 == 0)
		{
			cout << val << " ";
		}
		});
	cout << endl;
}
#endif