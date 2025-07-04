#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
* 回溯算法思想
*/

#if 0
void func(int arr[], int i, int length, int x[])
{
	if (i == length)  // 递归结束条件
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
		x[i] = 1;  // 选择i节点
		func(arr, i + 1, length, x);  // 遍历i的左孩子
		x[i] = 0;  // 不选择i节点
		func(arr, i + 1, length, x);  // 遍历i的右孩子
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

