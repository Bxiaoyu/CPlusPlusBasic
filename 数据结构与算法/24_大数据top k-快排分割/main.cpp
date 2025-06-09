#include <iostream>

using namespace std;

// 快排分割函数
int partition(int arr[], int begin, int end)
{
	int val = arr[begin];  // 基准数，可以采用三数取中方法
	int i = begin;
	int j = end;

	while (i < j)
	{
		while (i < j && arr[j] > val)  // 如果找大的，只要反方向比较就可以
		{
			j--;
		}
		if (i < j)
		{
			arr[i] = arr[j];
			i++;
		}

		while (i < j && arr[i] < val)
		{
			i++;
		}
		if (i < j)
		{
			arr[j] = arr[i];
			j--;
		}
	}

	arr[i] = val;
	return i;
}

void selectTopK(int arr[], int begin, int end, int k)
{
	int pos = partition(arr, begin, end);
	if (pos == k - 1)
	{
		return;
	}
	else if (pos > k - 1)
	{
		selectTopK(arr, begin, pos - 1, k);
	}
	else
	{
		selectTopK(arr, pos + 1, end, k);
	}
}

int main()
{
	int arr[] = { 64, 45, 52, 80, 66, 68, 0, 2, 18, 75 };
	int size = sizeof arr / sizeof arr[0];

	// 求值最小的前3个元素
	int k = 3;
	selectTopK(arr, 0, size - 1, k);

	for (int i = 0; i < k; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}