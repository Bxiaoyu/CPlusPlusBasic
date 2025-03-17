#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

/*
* 海量数据查重/去重和求Top K的问题
* 海量数据的查重问题：
* 1、哈希表 50亿（5G）个整数（20G+20G） 10亿（1G）
* 2、分治思想
* 3、布隆过滤器
* 4、针对字符串类型：TrieTree字典树（前缀树）
*/

/*
* 1、基本的数据查重思想
*/
void test_1()
{
	const int SIZE = 10000;
	int arr[SIZE] = { 0 };
	for (int i = 0; i < SIZE; ++i)
	{
		arr[i] = rand();
	}

	// 在上面SIZE数据量中，找出谁重复了，并且统计重复
	unordered_map<int, int> _map;
	for (int val : arr)
	{
		_map[val]++;
	}

	for (auto pair : _map)
	{
		if (pair.second > 1)
		{
			cout << "数字：" << pair.first << " 重复次数：" << pair.second << endl;
		}
	}
}

/*
* 2、有一个文件，有大量整数（50亿个），内存限制400M，找出文件中的重复元素和次数
* 50亿 5G * 4 = 20G * 2 = 40G
* 数据量过大，采用分治思想：
* 大文件划分为小文件，使得每一个小文件能够加载到内存当中，求出对应的重复元素，把结果写入一个存储重复元素的文件
* 
* 大文件-》小文件个数（40G/400M）
* data0.txt
* data1.txt
* ...
* data126.txt
* 
* 遍历大文件的元素，把每一个元素根据哈希映射函数，放到对应序号的小文件当中
* data % 127 = file_index
* 
* 值相同的，通过一样的哈希映射函数，肯定放在同一个小文件当中
*/
void test_2()
{
#if 0
	// 位列快速获取结果，缩小了数据规模
	FILE* pf1 = fopen("data.dat", "wb");
	for (int i = 0; i < 20000; ++i)
	{
		int data = rand();
		if (data < 0)
		{
			cout << data << endl;
		}
		fwrite(&data, 4, 1, pf1);
	}
	fclose(pf1);
#endif

	// 打开源数据
	FILE* pf = fopen("data.dat", "rb");
	if (pf == nullptr)
	{
		return;
	}

	const int FILE_NO = 11;
	FILE* pfile[FILE_NO] = { nullptr };
	for (int i = 0; i < FILE_NO; ++i)
	{
		char filename[20];
		sprintf(filename, "data%d.dat", i + 1);
		pfile[i] = fopen(filename, "wb+");
	}

	// 哈希映射，把大文件中的数据映射到各个小文件当中
	int data;
	while (fread(&data, 4, 1, pf) > 0)
	{
		int findex = data % FILE_NO;
		fwrite(&data, 4, 1, pfile[findex]);
	}

	// 定义一个链式哈希表
	unordered_map<int, int> numMap;
	// 先定义一个小根堆
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto& a, auto& b)->bool {
		return a.second > b.second;  // 自定义小根堆元素比较方式
		});

	// 分段求解小文件的top10大的数据，并求出最终结果
	for (int i = 0; i < FILE_NO; ++i)
	{
		// 恢复小文件的文件指针到起始位置
		fseek(pfile[i], 0, SEEK_SET);

		while (fread(&data, 4, 1, pfile[i]) > 0)
		{
			numMap[data]++;
		}

		int k = 0;
		auto it = numMap.begin();
		// 如果堆是空的，先往堆放10个数据
		if (minheap.empty())
		{
			// 从map表中读10个数据到小根堆，建立top 10的小根堆，最小的元素在堆顶
			for (;it != numMap.end() && k < 10;++it, ++k)
			{
				minheap.push(*it);
			}
		}

		// 把k+1到末尾的元素进行遍历，和堆顶元素进行对比
		for (;it != numMap.end();++it)
		{
			// 如果map表中当前元素重复次数大于堆顶元素的重复次数，则替换
			if (it->second > minheap.top().second)
			{
				minheap.pop();
				minheap.push(*it);
			}
		}

		// 清空哈希表，进行下一个小文件的数据统计
		numMap.clear();
	}

	// 堆中剩余的就是重复次数最大的前k个
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << ":" << pair.second << endl;
		minheap.pop();
	}
}


/*
* 3、
* a、b两个文件，里面都有10亿个整数，内存限制400M，求出a,b两个文件中的重复元素有哪些？
* 
* 10亿 -》1G * 4 = 4G*2 = 8G/400M = 27个小文件
* a-》全部读到内存中，存储到哈希表
* b-》从b文件读数据，在内存哈希表中查询
* 
* 把a和b两个文件，划分成个数相等的一系列（27）小文件（分治思想）
* a1.txt b1.txt
* a2.txt b2.txt
* a3.txt b3.txt
* ...
* a26.txt b26.txt
* 
* 从a文件中读取数据，通过 数据%27 = file_index
* 从b文件中读取数据，通过 数据%27 = file_index
* 
* a和b两个文件中，数据相同的元素，进行哈希映射以后，肯定在相同序号的小文件中
* 
* 处理a1和b1...直到a26和b26
*/

#if 0
int main()
{
	test_2();
	return 0;
}
#endif