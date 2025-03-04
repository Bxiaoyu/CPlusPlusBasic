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
#include <algorithm>  // 包含STL泛型算法
#include <functional>  // 包含函数对象和绑定器

using namespace std;

/*
* C++ STL standard template libaray 标准模板库
* 一、标准容器 C++11 array forward_list
* 容器中，对象的构造析构，内存的开辟释放，都是由空间配置器（allocator）来实现的，包括以下四个方法：
* allocate   分配空间
* deallocate 释放空间
* construct  构造对象
* destroy    析构对象
* 
* 1.顺序容器
* vector 动态开辟的数组，每次以原来空间大小的2倍进行扩容
* deque
* list
* 
* 2.容器适配器
* stack
* queue
* priority_queue
* 
* 3.关联容器
* 无序关联容器 -> 基于链式哈希表 增删查O(1)
* unordered_set
* unordered_multiset
* unordered_map
* unordered_multimap
* 
* 有序关联容器 -> 基于红黑树 增删查O(log2n) 2是底数（树的层数，树的高度）
* set
* multiset
* map
* multimap
* 
* 注意：map系列的operator[]（中括号）操作有两个功能：
* 1.查询；
* 2.如果key不存在，它会插入一对数据[key,v()]
* 
* 二、近容器
* 数组，string，bitset（位容器）
* 
* 三、迭代器
* iterator和const_iterator
* reverse_iterator和const_reverse_iterator
* 
* 四、函数对象（类似C的函数指针）
* greater，less
* 
* 五、泛型算法（很多，这里仅介绍几个常用的）
* sort，find，find_if，binary_search，for_each
*/

/*
* vector：向量容器
* 底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容
* 
* vector<int> vec;
* 增加：
* vec.push_back(20); 末尾添加元素O(1) 会导致容器扩容
* vec.insert(it, 20); it迭代器指向的位置添加一个元素20 O(N) 会导致容器扩容
* 
* 删除：
* vec.pop_back(); 删除末尾元素 O(1)
* vec.erase(it);  删除迭代器指向的元素 O(N)
* 
* 查询：
* operator[] 下标的随机访问vec[5] O(1)
* iterator迭代器进行遍历
* find，for_each
* foreach -> 底层通过iterator来实现的
* 
* 注意：对容器进行连续插入或者删除操作（insert/erase），一定要更新迭代器，否则第一次insert或者erase完成后，迭代器就失效了。
* 
* 常用方法介绍：
* size()
* empty()
* reserve(20); vector预留空间的，只给容器底层开辟指定大小的内存空间，并不会添加新元素
* resize(20);  容器扩容用的，不仅给容器底层开辟指定大小的内存空间，还会添加新元素
* swap(); 两个容器交换元素用
*/
#if 0
int main()
{
	vector<int> vec;
	//vec.reserve(20);  // vector容器预留空间 可以减少频繁扩容代价
	vec.resize(20);  // 开辟空间并初始化元素为0
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

	// 把容器中所有偶数删除
	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			it = vec.erase(it);  // 注意更新迭代器
		}
		else
		{
			++it;
		}
	}

	// 通过迭代器遍历容器
	auto it2 = vec.begin();
	for (;it2 != vec.end(); ++it2)
		cout << *it2 << " ";
	cout << endl;

	// 给vector容器中所有偶数前面添加一个小于奇数1的偶数 44 45
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
* 一、deque：双端队列容器
* 底层数据结构：动态开辟的二维数组，一维数组从2开始，以2倍的方式进行扩容，每次扩容后，原来第二维的数组，从新的第一维数组的
* 下标 oldsize/2 开始存放，上下都预留相同的空行，方便支持deque的首尾元素添加。
* 
* deque<int> deq;
* 增加：
* deq.push_back(20); 从尾部添加元素 O(1)
* deq.push_front(20); 从头部添加元素 O(1)
* deq.insert(it, 20); it指向的位置添加元素 O(N)
* 
* 删除：
* deq.pop_back(); 从末尾删除元素 O(1)
* deq.pop_front(); 从头部删除元素 O(1)
* deq.erase(it); 从it指向的位置删除元素 O(N)
* 
* 查询搜索：
* iterator（连续的insert和erase一定要考虑迭代器失效问题）
* 
* 二、list：链表容器
* 底层数据结构：双向的循环链表 pre data next
* 
* list<int> mylist;
* 增加：
* mylist.push_back(20); 从末尾添加元素 O(1)
* mylist.push_front(20); 从首部添加元素 O(1)
* mylist.insert(it, 20); it 指向的位置添加元素 O(1)
* 链表中进行insert操作时，需要进行query查询操作，对链表来说，查询操作效率比较慢
* 
* 删除：
* mylist.pop_back(); 从尾部删除元素 O(1)
* mylist.pop_front(); 从首部删除元素 O(1)
* mylist.erase(it);  从it指定的位置删除元素 O(1)
* 
* 查询搜索：
* iterator（连续的insert和erase一定要考虑迭代器失效问题）
* 
* 三、vector，deque，list比较：
* vector特点：动态数组，内存是连续的，2倍的方式进行扩容；
* deque特点：动态开辟的二维数组空间，第二维是固定长度的数组空间，扩容的时候（第一维的数组进行2倍扩容）；
* 面经问题：deque底层内存是否连续？并不是，每一个第二维数组是连续
* 
* 
* 容器的纵向考察：容器掌握的深度
* 容器的横向考察：相似容器之间的对比
* 
* vector和deque之间的区别：
* 1.底层数据结构区别；
* 2.前中后插入删除元素的时间复杂度：中间和末尾都是O(1)，前 deque O(1)，vector O(N)；
* 3.对于内存的使用效率：vector需要的内存空间必须是连续的，deque可以分块进行数据存储，内存空间不必是连续的；
* 4.在中间进行insert或erase，vector和deque哪个效率更好一点呢？虽然时间复杂度都是O(N)，但得益于vector是连续内存，所以vector更好一点；
* 
* vector和list之间的区别：
* 1.底层数据结构区别：
	- 数组：增加，删除，查询O(n)，随机访问O(1)
	- 双向循环列表：增加，删除O(1)（要考虑搜索时间）
*/


/*
* 一、标准容器-容器适配器 -> 类似于设计模式中的适配器模式
* 1、如何理解适配器？
* a.适配器底层没有自己的数据结构，它是对另一个容器的封装，它的方法全部由底层依赖的容器进行实现；
* b.适配器没有实现自己的迭代器；
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
* stack：push入栈 pop出栈 top栈顶元素 empty判空 size元素个数；
* queue：push入队 pop出队 front队头元素 back队尾元素 empty判空 size元素个数；
* priority_queue：push入队 pop出队 top队头元素 empty判空 size元素个数；默认大根堆结构；
* 
* 2、为什么 stack 和 queue 底层容器依赖deque而不是vector？
* a.vector的初始内存使用效率太低，没有deque好；vector 0-1-2-3-4 deque 4096；
* b.对于queue来说，需要支持尾部插入，头部删除，O(1)，依赖vector的话底层出队效率很低；
* c.vector需要大片连续内存，deque只需要分段的内存，当存储大量数据时，显然deque的内存利用率更好一些；
* 
* 3、为什么 priority_queue 底层容器依赖vector而不是deque？
* a.priority_queue底层默认把数据组成一个大根堆结构（数据访问靠下标运算），在一个内存连续的数组上构建一个
*   大根堆或者小根堆；
* b.deque内存并不连续，有些操作不方便；
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
* 有序关联容器
* set  元素不重复
* multiset  元素可以重复
* map  元素不重复
* multimap  元素可以重复
* 
* 注意：自定义数据类型使用有序关联容器set的时候，需要给数据类型提供小于<运算符的重载函数。
* bool operator<(const T& obj) const;
*/

#if 0
#define USE_SET 0
// 学生类
class Student
{
public:
	Student(int id, string name) 
		: id_(id)
		, name_(name)
	{}

	// 提供<运算符重载，以便有序关联容器能正常使用
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
	stuMap.insert({ 1000, Student(1000, "张三") });
	stuMap.insert({ 1002, Student(1002, "王五") });
	stuMap.insert({ 1001, Student(1001, "李四") });

	for (const auto& item : stuMap)
	{
		cout << item.second << endl;
	}

#if 0
	set<Student> st;
	st.insert(Student(1020, "赵四"));
	st.insert(Student(1001, "张三"));
	st.insert(Student(1002, "李四"));
	st.insert(Student(1003, "王五"));

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
* 无序关联容器
* 各个容器底层的数据结构 O(1)，O(log2n)
* unordered_set
* unordered_multiset
* unordered_map
* unordered_multimap
* 
* 常用增删改查方法：
* 增加：insert(val)
* 遍历：iterator
* 查找：find
* 删除：erase(key)，erase(it)
*/
#if 0
int main()
{
	// 处理海量数据查重复，去重复
	const int ARR_LEN = 100000;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i)
	{
		arr[i] = rand() % 10000 + 1;
	}

	// 上面的10万个数据中，把数据进行去重
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
	// 上面的10万个数据中，统计哪些数字重复了，并且重复了几次
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

		//map1[k]++; 也可以利用map的插入性质简化代码，即map[k]没查询到元素的话会自动插入一个
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
* 容器的迭代器iterator
* iterator：普通正向迭代器 begin(),end()
* const_iterator：常量的正向迭代器 只能读，不能写
* 
* reverse_iterator：普通反向迭代器，rbegin(),rend()
* const_reverse_iterator：常量的反向迭代器 只能读，不能写
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
		//	//*it1 = 0;  // const_iterator下不能修改
		//}
	}
	cout << endl;

	// rbegin()：返回的是最后一个元素的反向迭代器表示
	// rend()：返回的是首元素前驱位置的迭代器表示
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
* 函数对象 -》C语言里的函数指针
* 1、通过函数对象调用operator()，可以省略函数的调用开销，比通过函数指针调用函数（不能够inline内联调用）效率高；
* 2、因为函数对象是用类生成的，所以可以添加相关的成员变量，用来记录函数对象使用时更多的信息；
*/

#if 0
// 使用C的函数指针解决方案
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

// 使用C++函数对象解决方案
template<typename T>
class Greater
{
public:
	bool operator()(T a, T b)  // 二元函数对象
	{
		return a > b;
	}
};

template<typename T>
class Less
{
public:
	bool operator()(T a, T b)  // 二元函数对象
	{
		return a < b;
	}
};

// compare是C++的库函数模板
template<typename T, typename Compare>
bool compare(T a, T b, Compare comp)
{
	// 1.通过函数指针调用函数，是没有办法内联的，编译器在编译阶段不知道具体函数是谁，效率很低，因为有函数调用开销
	// 2.通过函数对象是可以内联的，省略调用开销 operator()(a,b)
	return comp(a, b);
}

int main()
{
	cout << compare(10, 20, myGreater<int>) << endl;  // 函数指针
	cout << compare(10, 20, myLess<int>) << endl;
	cout << compare(10, 20, Greater<int>()) << endl;  // 函数对象
	cout << compare(10, 20, Less<int>()) << endl;

	// 优先级队列
	priority_queue<int> que1;  // 默认大根堆
	using MinHeap = priority_queue<int, vector<int>, greater<int>>;  // 使用小根堆
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

	// 队列
	set<int> s1;  // 默认从小到大排序
	set<int, greater<int>> s2;  // 选择从大到小排序
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
* 泛型算法 = template + 迭代器 + 函数对象
* 特点：
* 1.泛型算法的参数接收的都是迭代器；
* 2.泛型算法的参数还可以接收函数对象（C函数指针）；
* sort，find，find_if，binary_search，for_each
* 
* 绑定器 + 二元函数对象 -》一元函数对象
* bind1st：把二元函数对象的operator()的第一个形参绑定起来
* bind2nd：把二元函数对象的operator()的第二个形参绑定起来
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

	sort(vec.begin(), vec.end());  // 默认小到大排序
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	if (binary_search(vec.begin(), vec.end(), 21))  // 有序容器中进行二分查找
	{
		cout << "binary_search:21存在" << endl;
	}
	
	auto it = find(vec.begin(), vec.end(), 21);  // 时间复杂度比binary_search高
	if (it != vec.end())
	{
		cout << "find:21存在" << endl;
	}

	// 传入函数对象greater，改变容器元素排序时的比较方式
	sort(vec.begin(), vec.end(), greater<int>());
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	/*
	* 98 78 63 56 21 12 10 9 4
	* 把48按序插入到vector容器当中，找第一个小于48的数字
	* find_if需要的是一个一元函数对象
	* greater a > b less a < b
	* 
	*/
	//auto it1 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 48));
	//auto it1 = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 48));  // 效果同上
	auto it1 = find_if(vec.begin(), vec.end(), [](int val)->bool {return val < 48;});  // 效果同上
	vec.insert(it1, 48);
	for (auto& val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	// for_each打印偶数
	for_each(vec.begin(), vec.end(), [](int val)->void {
		if (val % 2 == 0)
		{
			cout << val << " ";
		}
		});
	cout << endl;
}
#endif