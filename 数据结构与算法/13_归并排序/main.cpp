#include <iostream>

using namespace std;


// 归并过程函数  O(n)
void Merge(int arr[], int* p, int l, int m, int r)
{
	int i = l;
	int j = m + 1;
	int index = 0;

	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j])
		{
			p[index++] = arr[i++];
		}
		else
		{
			p[index++] = arr[j++];
		}
	}

	while (i <= m)
	{
		p[index++] = arr[i++];
	}

	while (j <= r)
	{
		p[index++] = arr[j++];
	}

	// 把合并好的大段有序结果，拷贝到原始数组arr[l,r]区间
	for (int i = l, j = 0; i <= r; i++, j++)
	{
		arr[i] = p[j];
	}
}

// 归并排序递归接口
void MergeSort(int arr[], int* p, int begin, int end)
{
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;

	// 先递
	MergeSort(arr, p, begin, mid);
	MergeSort(arr, p, mid + 1, end);

	// 归并 [begin, mid] [mid+1, end] 把两个小段有序的序列合并成大段有序序列
	Merge(arr, p, begin, mid, end);
}

// 归并排序
void MergeSort(int arr[], int size)
{
	int* p = new int[size];
	MergeSort(arr, p, 0, size - 1);
	delete[] p;
}

int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	MergeSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}