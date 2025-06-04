#include <iostream>

using namespace std;


// �鲢���̺���  O(n)
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

	// �Ѻϲ��õĴ����������������ԭʼ����arr[l,r]����
	for (int i = l, j = 0; i <= r; i++, j++)
	{
		arr[i] = p[j];
	}
}

// �鲢����ݹ�ӿ�
void MergeSort(int arr[], int* p, int begin, int end)
{
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;

	// �ȵ�
	MergeSort(arr, p, begin, mid);
	MergeSort(arr, p, mid + 1, end);

	// �鲢 [begin, mid] [mid+1, end] ������С����������кϲ��ɴ����������
	Merge(arr, p, begin, mid, end);
}

// �鲢����
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