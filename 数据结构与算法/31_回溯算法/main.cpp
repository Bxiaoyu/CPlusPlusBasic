#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
* �����㷨˼��
*/

#if 0
void func(int arr[], int i, int length, int x[])
{
	if (i == length)  // �ݹ��������
	{
		for (int j = 0; j < length; j++)
		{
			if(x[j] == 1)
				cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		x[i] = 1;  // ѡ��i�ڵ�
		func(arr, i + 1, length, x);  // ����i������
		x[i] = 0;  // ��ѡ��i�ڵ�
		func(arr, i + 1, length, x);  // ����i���Һ���
	}
}

int main()
{
	int arr[] = { 1,2,3 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int x[3] = { 0 };
	func(arr, 0, length, x);
	return 0;
}
#endif

/*
* ����ѡ�����⣺����һ�����飬����������һ����������������֮����ʣ�µ�����֮�͵Ĳ���С
*/
int arr[7] = { 12,6,7,11,16,3,8 };
//const int length = sizeof(arr) / sizeof(arr[0]);
const int length = 7;
int x[7] = { 0 };  // �Ӽ����������飬��¼�ڵ��������ӻ����Һ��ӡ�����i�ڵ㱻ѡ��&δ��ѡ��
int bestx[7] = { 0 };  // ��¼���Ž�
unsigned int minNum = 0xFFFFFFFF;  // ��¼��С�Ĳ�ֵ
int sum = 0;  // ��¼��ѡ�Ӽ����ֵ��ܺ�
int r = 0;  // ��¼δѡ�����ֵĺ�

// �����Ӽ���
void func(int i)
{
	if (i == length)
	{
		int result = abs(sum - r);
		if (result < minNum)
		{
			minNum = result;
			// ��Ҫ��¼һ�²�ֵ��С���Ӽ�
			for (int j = 0; j < length; j++)
			{
				bestx[j] = x[j];
			}
		}
	}
	else
	{
		r -= arr[i];
		sum += arr[i];
		x[i] = 1;
		func(i + 1);  // ѡ��i�ڵ�
		sum -= arr[i];
		r += arr[i];

		x[i] = 0;
		func(i + 1);  // ��ѡ��i�ڵ�
	}
}

int main()
{
	for (int v : arr)
	{
		r += v;
	}

	func(0);

	for (int i = 0; i < length; i++)
	{
		if (bestx[i] == 1)
		{
			cout << arr[i] << " ";
		}
	}
	cout << endl;
	cout << "min:" << minNum << endl;

	return 0;
}