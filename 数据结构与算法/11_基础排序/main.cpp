#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
* 基础排序
*/

// 冒泡排序算法
void BubbleSort(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)  // 比较趟数
	{
		bool flag = false;  // 优化条件
		for (int j = 0; j < size - 1 - i; j++)  // 一趟的处理
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = true;
			}
		}

		if (!flag)
		{
			// 如果没有任何我数据交换，说明数据已经有序
			return;
		}
	}
}

// 选择排序算法 O(n) * O(n) = O(n^2)   空间复杂度： O(1)   稳定性：不稳定    
// 5 5 3
void ChoiceSort(int arr[], int size)
{
	for (int i = 0; i < size-1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
		}

		// 找到后面剩余序列中的最小值，和开始位置的值进行交换
		if (minIndex != i)
		{
			int temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
}

// 插入排序算法  时间复杂度: 最坏、平均 O(n^2)  最好：O(n)  空间：O(1)  稳定性：稳定的
void InsertSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int val = arr[i];
		int j = i - 1;
		for (;j >= 0;j--)
		{
			if (arr[j] <= val)
			{
				break;
			}
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = val;
	}
}

#if 0
int main()
{
	const int COUNT = 100000;
	int* arr = new int[COUNT];
	int* brr = new int[COUNT];
	int* crr = new int[COUNT];
	int* drr = new int[COUNT];

	srand(time(NULL));

	for (int i = 0; i < COUNT; i++)
	{
		int val = rand() % COUNT;
		arr[i] = val;
		brr[i] = val;
		crr[i] = val;
		drr[i] = val;
	}

	clock_t begin, end;

	begin = clock();
	BubbleSort(arr, COUNT);
	end = clock();
	cout << "BubbleSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	//begin = clock();
	//ChoiceSort(brr, COUNT);
	//end = clock();
	//cout << "ChoiceSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	//begin = clock();
	//InsertSort(crr, COUNT);
	//end = clock();
	//cout << "InsertSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

	//begin = clock();
	//ShellSort(drr, COUNT);
	//end = clock();
	//cout << "ShellSort spend:" << (end - begin) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
}
#endif

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

	//BubbleSort(arr, 10);
	//ChoiceSort(arr, 10);
	InsertSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}