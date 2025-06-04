#include <iostream>

using namespace std;

// 快排分割函数，返回基准数位置
int Partition(int arr[], int l, int r)
{
	// 选择基准数的优化：“三数取中”法   arr[l]   arr[r]   arr[(l+r)/2]  
	// 记录基准数
	int val = arr[l];

	// 一次快排处理
	while (l < r)
	{
		while (l < r && arr[r] > val)
		{
			r--;
		}

		if (l < r)
		{
			arr[l] = arr[r];
			l++;
		}

		while (l < r && arr[l] < val)
		{
			l++;
		}

		if (l < r)
		{
			arr[r] = arr[l];
			r--;
		}
	}

	// l == r的位置，就是放基准数的位置
	arr[l] = val;
	return l;
}


// 快排递归接口
void QuickSort(int arr[], int begin, int end)
{
	if (begin >= end)  // 快排递归结束条件
		return;

	//// 随着快排算法执行，小范围趋于有序的数据采用插入排序优化性能
	//if (end - begin == 100)
	//{
	//	InsertSort(arr, begin, end);
	//	return;
	//}

	// 在[begin,end]区间的元素做一次快排分割
	int pos = Partition(arr, begin, end);

	// 对基准数的左边和右边序列，再进行快排
	QuickSort(arr, begin, pos - 1);
	QuickSort(arr, pos + 1, end);
}

// 快速排序
void QuickSort(int arr[], int size)
{
	QuickSort(arr, 0, size - 1);
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

	QuickSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}