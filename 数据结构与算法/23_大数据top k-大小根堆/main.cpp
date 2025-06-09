#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <ctime>

using namespace std;

// ���غ�TopK������
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

	// 1��ͳ���ظ��������ٵ�ǰ3����
	// �������ѵ�ʱ��Ҫ����key-value��ֵ��
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

	// ���
	while (!maxHeap.empty())
	{
		cout << maxHeap.top().first << ":" << maxHeap.top().second << endl;
		maxHeap.pop();
	}
	cout << endl;
#endif

	// 2��ͳ���ظ���������ǰ3����
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

	// ��ǰ�������ֹ���С����
	auto it = m2.begin();
	for (int i = 0; i < 3; i++, it++)
	{
		minHeap.push(*it);
	}

	// ����ʣ��Ԫ��
	for (;it != m2.end(); it++)
	{
		if (it->second > minHeap.top().second)
		{
			minHeap.pop();
			minHeap.push(*it);
		}
	}

	// ���
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
	// ��vec��ֵ��С��ǰ5��Ԫ��
	priority_queue<int> maxHeap;
	// ��ǰk��Ԫ�ع���һ�������
	for (int i = 0; i < 5; i++)
		maxHeap.push(vec[i]);

	// ����ʣ��Ԫ��
	for (int i = 5; i < vec.size(); i++)
	{
		if (vec[i] < maxHeap.top())
		{
			maxHeap.pop();
			maxHeap.push(vec[i]);
		}
	}

	cout << "ֵ��С��ǰ5��Ԫ��Ϊ��";
	while (!maxHeap.empty())
	{
		cout << maxHeap.top() << " ";
		maxHeap.pop();
	}
	cout << endl;
#endif

#if 0
	// ��vec��ֵ����ǰ5��Ԫ��
	priority_queue<int, vector<int>, greater<int>> minHeap;
	// ��ǰk��Ԫ�ع���һ��С����
	for (int i = 0; i < 5; i++)
		minHeap.push(vec[i]);

	// ����ʣ��Ԫ��
	for (int i = 5; i < vec.size(); i++)
	{
		if (vec[i] > minHeap.top())
		{
			minHeap.pop();
			minHeap.push(vec[i]);
		}
	}

	// ������
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