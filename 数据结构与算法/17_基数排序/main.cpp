#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

/*
* 基数排序（桶排序）步骤：
* 1、找出最大的数字，确定要处理的桶排序的趟数（即最大数字位数）；
* 2、依次由个位开始处理，把相应位数上的数字，放入相应序号的桶里，完成后，再按照桶的序号，
*    依次取出桶里的数据，放回原始的数组当中；
* 3、当处理完所有的位数，最终得到有序的序列。
* 
*/

// 基数排序代码
// 时间复杂度：O(nd)  空间复杂度:O(n)  稳定性：稳定的排序
void RadixSort(int arr[], int size)
{
	// 1、找到最大值并获取其位数
	int maxData = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (maxData < abs(arr[i]))
			maxData = abs(arr[i]);
	}
	int len = to_string(maxData).size();

	vector<vector<int>> vecs;
	int mod = 10;
	int dev = 1;
	for (int i = 0; i < len; mod *= 10, dev *= 10, i++)
	{
		//vecs.resize(10);
		vecs.resize(20);  // 20个桶，为了能处理负数 -9 ~ 9

		// 将数据根据数位的数值放入对应序号的桶
		for (int j = 0; j < size; j++)
		{
			//int index = arr[j] % mod / dev;
			int index = arr[j] % mod / dev + 10;  // 为了能处理负数，需要+10
			vecs[index].push_back(arr[j]);
		}

		// 依次遍历所有的桶，把元素拷贝回原始数组
		int idx = 0;
		for (auto vec : vecs)  // O(20)
		{
			for (auto v : vec)  // O(n)    O(20)*O(n) = O(n)
			{
				arr[idx++] = v;
			}
		}

		vecs.clear();
	}
}

int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	arr[9] = -123;
	arr[6] = -38;

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	RadixSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}