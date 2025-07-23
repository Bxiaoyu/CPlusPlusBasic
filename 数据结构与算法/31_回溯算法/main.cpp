#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
* 回溯算法思想
*/

/*
* 解空间-子集树
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

#if 0
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
int leftcnt = length;  // 记录未处理的数字的个数

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
		leftcnt--;
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
		if(x.size() + leftcnt >= length / 2)
			func(i + 1);  // 遍历i的右孩子，表示不选择i号位元素

		// 当前i节点已处理完，回溯到其父节点
		leftcnt++;
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
#endif

/*
* 挑选数字：有一组整数，请挑选出一组数字，让它们的和等于指定的值，存在打印，不存在打印
*/
#if 0
int arr[] = { 4,8,12, 16,7,3,9 };
const int length = sizeof(arr) / sizeof(arr[0]);
int target = 18;
vector<int> x;   // 记录选择的数字
int sum = 0;     // 记录所选数字的和
int r = 0;       // 记录未处理数字的总和

void func(int i)
{
	if (i == length)
	{
		if (sum != target)
		{
			return;
		}
		
		for (int v : x)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		r -= arr[i];  // 处理当前i节点
		if (sum + arr[i] <= target)  // 剪左树枝  已选择数字的和 + 即将要选择的数字
		{
			x.push_back(arr[i]);
			sum += arr[i];
			func(i + 1);
			x.pop_back();
			sum -= arr[i];
		}

		if (sum + r >= target)  // 剪右树枝  已选择数字的和 + 剩余的可以被选择的数字的和（i+1, i+2...n）
		{
			func(i + 1);
		}
		r += arr[i];
	}
}

int main()
{
	for (int v : arr)
	{
		r += v;
	}

	func(0);

	return 0;
}
#endif
#if 0
// 更高效的写法，N叉树
int arr[] = { 4,8,12, 16,7,3,9,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int target = 18;
vector<int> vec;   // 记录选择的数字

void func(int i, int number)
{
	if (number == 0)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		// 以当前节点开始，把剩余元素的孩子节点生成
		for (int k = i; k < length; ++k)
		{
			if (number >= arr[k])  // 剩下待选元素要小于number
			{
				vec.push_back(arr[k]);
				// 当前层遍历到下一层时 arr[k] != arr[k-1]
				// 不允许选择重复元素
				func(k + 1, number - arr[k]);  // 遍历孩子节点，arr[k]的孩子节点
				// 允许选择重复元素
				//func(k, number - arr[k]);
				vec.pop_back();
			}
		}
	}
}

int main()
{
	func(0, target);
	return 0;
}
#endif

/*
* 0-1背包问题：有一组物品，其重量分别为：w1,w2,w3...wn，其价值分别为：v1,v2,v3...vn，现在有一个背包，其容量位C,
* 问怎么把物品装入背包，能够使背包的价值最大化？
*/
#if 0
int w[] = { 12,5,8,9,6 };  // 物品重量
int v[] = { 9,11,4,7,8 };  // 物品价值
const int length = sizeof(w) / sizeof(w[0]);
vector<int> x;  // 选择的物品
vector<int> bestx;  // 记录最优选择的物品
int c = 20;     // 背包的容量
int cw = 0;     // 已选择物品的重量
int cv = 0;     // 已选择物品的价值
int maxV = 0;   // 记录装入背包的物品的最大价值
int r = 0;      // 未处理物品的总价值

void func(int i)
{
	if (i == length)
	{
		if (maxV < cv)
		{
			maxV = cv;
			bestx = x;
		}
	}
	else
	{
		r -= v[i];
		if (cw + w[i] <= c)  // 已选择物品的重量 + 即将选择的物品的重量
		{
			x.push_back(w[i]);
			cw += w[i];
			cv += v[i];
			func(i + 1);
			x.pop_back();
			cw -= w[i];
			cv -= v[i];
		}

		// maxV cv + [i+1...n]总价值 > maxV
		if (cv + r > maxV)
		{
			func(i + 1);
		}
		r += v[i];
	}
}

int main()
{
	for (int val : v)
	{
		r += val;
	}

	func(0);

	for (int w : bestx)
	{
		cout << w << " ";
	}
	cout << endl;
	cout << "maxV:" << maxV << endl;
	return 0;
}
#endif

/*
* 解空间-排列树代码模板
*/
#if 0
void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void func(int arr[], int i, int length)
{
	if (i == length)
	{
		for (int j = 0; j < length; ++j)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		// 生成i节点的所有孩子节点
		for (int k = i; k < length; ++k)
		{
			swap(arr, i, k);
			func(arr, i + 1, length);
			swap(arr, i, k);  // 一定要再交换回来
		}
	}
}

int main()
{
	int arr[] = { 1,2,3,4 };
	int length = sizeof(arr) / sizeof(arr[0]);
	func(arr, 0, length);

	return 0;
}
#endif

/*
* 排列树解决八皇后问题
*/
int cnt = 0;  // 统计排列总数

void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

bool judge(int arr[], int i)  // i表示当前放置皇后棋子的位置
{
	for (int j = 0; j < i; ++j)
	{
		if (i == j || arr[i] == arr[j] || abs(i-j) == abs(arr[i] - arr[j]))
		{
			return false;
		}
	}

	return true;
}

void func(int arr[], int i, int length)
{
	if (i == length)
	{
		cnt++;
		for (int j = 0; j < length; ++j)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < length; ++k)
		{
			swap(arr, i, k);
			if(judge(arr, i))  // 判断第i个位置的元素是否符合八皇后的条件
				func(arr, i+1, length);  // 生成孩子节点，即一系列排列方式
			swap(arr, i, k);
		}
	}
}

int main()
{
	// 把arr的下标当作行，下标对应的元素值当作列
	int arr[] = { 1,2,3,4,5,6,7,8 };
	int n = 8;
	func(arr, 0, n);
	cout << "总共: " << cnt << " 种." << endl;
	return 0;
}