#include <iostream>

using namespace std;

// 二分搜索算法非递归实现
int BinarySearch(int arr[], int size, int val)
{
	int first = 0;
	int last = size - 1;

	while (first <= last)
	{
		//int mid = (first + last) / 2;
		int mid = first + (last - first) / 2;  // 防止值溢出
		if (arr[mid] == val)
		{
			return mid;
		}
		else if (arr[mid] > val)
		{
			last = mid - 1;
		}
		else
		{
			first = mid + 1;
		}
	}

	return -1;
}

// 二分搜索算法递归实现
// 在[i...j]范围内寻找val
int BinarySearch(int arr[], int i, int j, int val)
{
	if (i > j)  // 递归结束条件
	{
		return -1;
	}

	int mid = i + (j - i) / 2;
	if (arr[mid] == val)
	{
		return mid;
	}
	else if (arr[mid] > val)
	{
		return BinarySearch(arr, i, mid - 1, val);
	}
	else
	{
		return BinarySearch(arr, mid + 1, j, val);
	}
}

// 测试递归
int TestBinarySearch(int arr[], int size, int val)
{
	return BinarySearch(arr, 0, size - 1, val);
}

int main()
{
	int arr[] = { 12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100 };
	int size = sizeof arr / sizeof arr[0];

	cout << "非递归----------" << endl;
	cout << BinarySearch(arr, size, 39) << endl;
	cout << BinarySearch(arr, size, 45) << endl;
	cout << BinarySearch(arr, size, 12) << endl;
	cout << BinarySearch(arr, size, 64) << endl;

	cout << "递归------------" << endl;
	cout << TestBinarySearch(arr, size, 39) << endl;
	cout << TestBinarySearch(arr, size, 45) << endl;
	cout << TestBinarySearch(arr, size, 12) << endl;
	cout << TestBinarySearch(arr, size, 64) << endl;
}