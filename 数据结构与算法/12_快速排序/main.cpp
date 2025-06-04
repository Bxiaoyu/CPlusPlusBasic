#include <iostream>

using namespace std;

// ���ŷָ�������ػ�׼��λ��
int Partition(int arr[], int l, int r)
{
	// ѡ���׼�����Ż���������ȡ�С���   arr[l]   arr[r]   arr[(l+r)/2]  
	// ��¼��׼��
	int val = arr[l];

	// һ�ο��Ŵ���
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

	// l == r��λ�ã����ǷŻ�׼����λ��
	arr[l] = val;
	return l;
}


// ���ŵݹ�ӿ�
void QuickSort(int arr[], int begin, int end)
{
	if (begin >= end)  // ���ŵݹ��������
		return;

	//// ���ſ����㷨ִ�У�С��Χ������������ݲ��ò��������Ż�����
	//if (end - begin == 100)
	//{
	//	InsertSort(arr, begin, end);
	//	return;
	//}

	// ��[begin,end]�����Ԫ����һ�ο��ŷָ�
	int pos = Partition(arr, begin, end);

	// �Ի�׼������ߺ��ұ����У��ٽ��п���
	QuickSort(arr, begin, pos - 1);
	QuickSort(arr, pos + 1, end);
}

// ��������
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