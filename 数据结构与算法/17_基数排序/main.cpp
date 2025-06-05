#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

/*
* ��������Ͱ���򣩲��裺
* 1���ҳ��������֣�ȷ��Ҫ�����Ͱ��������������������λ������
* 2�������ɸ�λ��ʼ��������Ӧλ���ϵ����֣�������Ӧ��ŵ�Ͱ���ɺ��ٰ���Ͱ����ţ�
*    ����ȡ��Ͱ������ݣ��Ż�ԭʼ�����鵱�У�
* 3�������������е�λ�������յõ���������С�
* 
*/

// �����������
// ʱ�临�Ӷȣ�O(nd)  �ռ临�Ӷ�:O(n)  �ȶ��ԣ��ȶ�������
void RadixSort(int arr[], int size)
{
	// 1���ҵ����ֵ����ȡ��λ��
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
		vecs.resize(20);  // 20��Ͱ��Ϊ���ܴ����� -9 ~ 9

		// �����ݸ�����λ����ֵ�����Ӧ��ŵ�Ͱ
		for (int j = 0; j < size; j++)
		{
			//int index = arr[j] % mod / dev;
			int index = arr[j] % mod / dev + 10;  // Ϊ���ܴ���������Ҫ+10
			vecs[index].push_back(arr[j]);
		}

		// ���α������е�Ͱ����Ԫ�ؿ�����ԭʼ����
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