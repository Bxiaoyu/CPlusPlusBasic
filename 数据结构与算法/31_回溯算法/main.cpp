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

/*
* 整数选择问题：给定一组数组，从里面挑出一组数，并让其整数之和与剩下的整数之和的差最小
*/
int arr[7] = { 12,6,7,11,16,3,8 };
//const int length = sizeof(arr) / sizeof(arr[0]);
const int length = 7;
int x[7] = { 0 };  // 子集树辅助数组，记录节点走向左孩子还是右孩子。代表i节点被选择&未被选择
int bestx[7] = { 0 };  // 记录最优解
unsigned int minNum = 0xFFFFFFFF;  // 记录最小的差值
int sum = 0;  // 记录所选子集数字的总和
int r = 0;  // 记录未选择数字的和

// 生成子集树
void func(int i)
{
	if (i == length)
	{
		int result = abs(sum - r);
		if (result < minNum)
		{
			minNum = result;
			// 需要记录一下差值最小的子集
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
		func(i + 1);  // 选择i节点
		sum -= arr[i];
		r += arr[i];

		x[i] = 0;
		func(i + 1);  // 不选择i节点
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