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

