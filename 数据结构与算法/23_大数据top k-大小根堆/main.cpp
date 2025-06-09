#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <ctime>

using namespace std;

// 查重和TopK问题结合
int main()
{
	vector<int> vec;
	srand(time(NULL));

	for (int i = 0; i < 10000; i++)
	{
		vec.emplace_back(rand() % 1000);
	}

#if 0
	unordered_map<int, int> m;
	for (auto key : vec)
	{
		m[key]++;
	}

	// 1、统计重复次数最少的前3个数
	// 放入大根堆的时候，要放入key-value键值对
	using Type = pair<int, int>;
	using Comp = function<bool(const Type&, const Type&)>;
	priority_queue<Type, vector<Type>, Comp> maxHeap(
		[](const Type& a, const Type& b)->bool
		{
			return a.second < b.second;
		}
	);

	auto it = m.begin();
	for (int i = 0; i < 3; i++, it++)
	{
		maxHeap.push(*it);
	}

	for (;it != m.end(); it++)
	{
		if (it->second < maxHeap.top().second)
		{
			maxHeap.pop();
			maxHeap.push(*it);
		}
	}

	// 输出
	while (!maxHeap.empty())
	{
		cout << maxHeap.top().first << ":" << maxHeap.top().second << endl;
		maxHeap.pop();
	}
	cout << endl;
#endif

	// 2、统计重复次数最多的前3个数
	unordered_map<int, int> m2;
	for (auto key : vec)
	{
		m2[key]++;
	}

	using Type = pair<int, int>;
	using Comp = function<bool(const Type&, const Type&)>;
	priority_queue<Type, vector<Type>, Comp> minHeap(
		[](const Type& a, const Type& b)->bool
		{
			return a.second > b.second;
		}
	);

	// 用前三个数字构建小根堆
	auto it = m2.begin();
	for (int i = 0; i < 3; i++, it++)
	{
		minHeap.push(*it);
	}

	// 遍历剩余元素
	for (;it != m2.end(); it++)
	{
		if (it->second > minHeap.top().second)
		{
			minHeap.pop();
			minHeap.push(*it);
		}
	}

	// 输出
	while (!minHeap.empty())
	{
		cout << minHeap.top().first << ":" << minHeap.top().second << endl;
		minHeap.pop();
	}

	return 0;
}

#if 0
int main()
{
	vector<int> vec;
	srand(time(NULL));

	for (int i = 0; i < 1000; i++)
	{
		vec.emplace_back(rand() % 10000);
	}

#if 0
	// 求vec中值最小的前5个元素
	priority_queue<int> maxHeap;
	// 由前k个元素构成一个大根堆
	for (int i = 0; i < 5; i++)
		maxHeap.push(vec[i]);

	// 遍历剩余元素
	for (int i = 5; i < vec.size(); i++)
	{
		if (vec[i] < maxHeap.top())
		{
			maxHeap.pop();
			maxHeap.push(vec[i]);
		}
	}

	cout << "值最小的前5个元素为：";
	while (!maxHeap.empty())
	{
		cout << maxHeap.top() << " ";
		maxHeap.pop();
	}
	cout << endl;
#endif

#if 0
	// 求vec中值最大的前5个元素
	priority_queue<int, vector<int>, greater<int>> minHeap;
	// 由前k个元素构成一个小根堆
	for (int i = 0; i < 5; i++)
		minHeap.push(vec[i]);

	// 遍历剩余元素
	for (int i = 5; i < vec.size(); i++)
	{
		if (vec[i] > minHeap.top())
		{
			minHeap.pop();
			minHeap.push(vec[i]);
		}
	}

	// 输出结果
	while (!minHeap.empty())
	{
		cout << minHeap.top() << " ";
		minHeap.pop();
	}
	cout << endl;
#endif
	return 0;

}
#endif