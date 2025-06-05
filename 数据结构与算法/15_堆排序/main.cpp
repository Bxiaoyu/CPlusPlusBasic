#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
* 堆排序的过程：
* ‌1、建堆‌：将待排序的序列构造成一个最大堆或最小堆，以满足堆的性质；
‌* 2、排序‌：将堆顶元素（最大或最小）与堆尾元素交换，然后减小堆的大小并重新调整剩余元素构成一个新的堆，重复此过程直到整个序列有序。
*/

// 堆的下沉调整
void ShiftDown(int arr[], int i, int size)
{
	int val = arr[i];
	// i下沉不能超过最后一个有孩子的节点
	while (i < size / 2)  // 或者 i <= size / 2 - 1
	{
		int child = i * 2 + 1;  // 左孩子
		if (((child + 1) < size) && (arr[child+1] > arr[child]))  // 存在右孩子，且右孩子值比左孩子值大
		{
			child = child + 1;  // 更新为右孩子下标
		}

		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child;
		}
		else
		{
			break;
		}
	}
	arr[i] = val;
}

// 堆排序
void HeapSort(int arr[], int size)
{
	int n = size - 1;
	// 先建立一个大根堆
	// 从第一个非叶子节点开始，逐个下沉
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		ShiftDown(arr, i, size);
	}

	// 对大根堆进行排序
	// 把堆顶元素和末尾元素进行交换，从堆顶开始进行下沉操作
	for (int i = n; i > 0; i--)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		ShiftDown(arr, 0, i);  // 第三个参数，参与调整的元素的个数
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

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	HeapSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}