#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

/*
* 海量数据求Top K的问题
* 1、求最大/最小的前K个元素
* 2、求最大/最小的第K个元素
* 
* 
* 解法1：大根堆/小根堆（优先级队列）
* 
* 1000个整数，找值前10大的元素
* 先用前10个整数创建一个小根堆（最小值就在堆顶），然后遍历剩下的整数，如果整数比堆顶元素大，那么删除堆顶元素
* 把整数入堆，遍历完所有整数，小根堆里存放的就是值最大的前十个元素了；如果找的是第K小的（大根堆堆顶）或者第K大
* （小根堆堆顶），只需访问堆顶一个元素
* 
* 大根堆 -》找Top k小的
* 小根堆 -》找Top k大的
* 
* 解法2：快排分割函数（一般来说效率更高）
* 
* 经过快排分割函数，能够在O(lgn)时间内，把小于基准数的整数调整到左边，把大于基准数的整数调整到右边，基准数（index）就可以认为
* 是第（index+1）小的整数了，[0,index]就是前index+1小的整数了
*/

/*
* 小根堆
*/
void test_minheap()
{
	// 求容器中元素值最大的前十个数
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}

	// 先定义小根堆
	priority_queue<int, vector<int>, greater<int>> minHeap;
	// 先往小根堆放入10个元素
	int k = 0;
	for (;k < 10;++k)
	{
		minHeap.push(vec[k]);
	}

	// 遍历剩下的整数，如果整数比堆顶元素大，那么删除堆顶元素
	// 把整数入堆，遍历完所有整数，小根堆里存放的就是值最大的前十个元素了；如果找的是第K小的（大根堆堆顶）或者第K大
    //（小根堆堆顶），只需访问堆顶一个元素
	for (;k < vec.size();++k)
	{
		if (minHeap.top() < vec[k])
		{
			minHeap.pop();
			minHeap.push(vec[k]);
		}
	}

	cout << "第10小的元素：" << minHeap.top() << endl;

	cout << "前10大的元素：";
	// 打印结果
	while (!minHeap.empty())
	{
		cout << minHeap.top() << " ";
		minHeap.pop();
	}
	cout << endl;
}

/*
* 快排分割
*/
int partation(vector<int>& arr, int i, int j)
{
	int k = arr[i];
	while (i < j)
	{
		while (i < j && arr[j] >= k)
		{
			j--;
		}
		if (i < j)
		{
			arr[i++] = arr[j];
		}
		while (i < j && arr[i] < k)
		{
			i++;
		}
		if (i < j)
		{
			arr[j--] = arr[i];
		}
	}

	arr[i] = k;
	return i;
}

int selectNoK(vector<int>& arr, int i, int j, int k)
{
	int pos = partation(arr, i, j);
	if (pos == k-1)
	{
		return pos;
	}
	else if (pos < k - 1)
	{
		return selectNoK(arr, pos + 1, j, k);
	}
	else
	{
		return selectNoK(arr, i, pos - 1, k);
	}
}

void test_quick_sort_split()
{
	// 求容器中第10小的元素值，前10小
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}

	// 返回的就是第十小的元素的值
	int index = selectNoK(vec, 0, vec.size() - 1, 10);
	cout << "第10小的元素：" << vec[index] << endl;
	cout << "前10小的元素：";
	for (int i = 0; i <= index; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

/*
* 查重和top k综合应用
* 
* 在一组数据中，找出重复次数最多的前10个
* 
* 如果数据很大，内存有限制，需要用分治思想分割数据到不同文件
*/
void test_top_k()
{
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}

	unordered_map<int, int> numMap;
	for (auto val : vec)
	{
		numMap[val]++;  // 如果val不存在，会直接插入一个
	}

	// 先定义小根堆
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto& a, auto& b)->bool
		{
			return a.second > b.second;  // 自定义小根堆元素的比较方式
		});

	// 先往堆放k个数据
	int k = 0;
	auto it = numMap.begin();
	// 先从map表中读取10个数据到小根堆中，建立top10的小根堆，最小元素在堆顶
	for (;it != numMap.end() && k < 10;++it, ++k)
	{
		minheap.push(*it);
	}

	// 把k+1到末尾的元素进行遍历，和堆顶元素进行比较
	for (;it != numMap.end();++it)
	{
		if (it->second > minheap.top().second)
		{
			minheap.pop();
			minheap.push(*it);
		}
	}

	// 堆中剩下的就是重复次数最大的前k个
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << ":" << pair.second << endl;
		minheap.pop();
	}
}

#if 0
int main()
{
	//test_minheap();
	//test_quick_sort_split();
	test_top_k();
	return 0;
}
#endif