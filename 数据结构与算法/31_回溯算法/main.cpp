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

#if 0
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
#endif

/*
* 整数选择问题：给定2n个整数，从里面挑出n个整数，并让其整数之和与剩下的整数之和的差最小
*/
vector<int> arr = { 12,6,7,11,16,3,8,9 };
int length = arr.size();
vector<int> x;      // 记录子集中选择的元素
vector<int> bestx;  // 记录最优解
int sum = 0;        // 记录子集中所选数字的和
int r = 0;          // 记录未选择数字的和
unsigned int minNum = 0xFFFFFFFF;  // 记录最小差值
int cnt = 0;        // 记录遍历的子集个数，用于测试

void func(int i)
{
	if (i == length)
	{
		// 得到子集树的一个解，对应一个叶子节点
		cnt++;
		if (x.size() != length / 2)
		{
			return;
		}

		int result = abs(sum - r);
		if (result < minNum)
		{
			minNum = result;
			bestx = x;
		}
	}
	else
	{
		if (x.size() < length / 2)  // 剪左树枝，提高算法效率，选择数字的前提：还未选择够n个整数
		{
			sum += arr[i];
			r -= arr[i];
			x.push_back(arr[i]);
			func(i + 1);  // 遍历i的左孩子，表示选择i号位元素
			sum -= arr[i];
			r += arr[i];
			x.pop_back();
		}

		// 这里右树枝能不能减呢？已选择数字的个数 + 未来能选择的所有数字的个数(i+1,i+2...n) >= n个元素
		func(i + 1);  // 遍历i的右孩子，表示不选择i号位元素
	}
}

int main()
{
	for (int v : arr)
	{
		r += v;
	}

	func(0);

	for (int v : bestx)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min: " << minNum << endl;
	cout << "cnt: " << cnt << endl;
	return 0;
}