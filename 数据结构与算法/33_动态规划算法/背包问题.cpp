#include <iostream>

using namespace std;


/*
* 0-1背包问题：
* 有一组物品，
* 其重量为w1、w2...wn，
* 其价值为v1、v2...vn，
* 现有一背包，其容量是c，问怎么装入物品，可以使背包的价值最大。
* 
* 
* 动规两个要素：
* 1、拥有最优子结构；
* 2、划分的子问题非独立（有重叠）
* 
* 状态（描述子问题最优解的性质）：
* 重量、价值、背包容量
* dp(i,j)：所选物品范围在i...n，背包容量为j，背包所容纳物品的最大价值
* 
* 状态转移方程（由子问题的最优解如何合并出原问题的最优解）：
* i == n：只考虑一个物品，就是wn
* wn > j：说明第n个物品无法装入背包
* dp[n][j] = 0
* wn <= j：说明第n个物品可以装入背包
* dp[n][j] = vn
* 
* i,i+1,i+2...n是可选物品
* wi > j：说明第i个物品无法放入背包
* dp[i][j] = dp[i+1][j]
* wi <= j：说明第i个物品可以放入背包 装入物品i/不装入物品i（取最大价值）
* dp[i][j] = max{dp[i+1][j], vi + dp[i+1][j-wi]}
* 
* 
* No      1 2 3 4 5 6  7  8  9  10 11 12  c=12
* 1(8,6)  0 8 8 8 8 15 15 15 15 15 21 21  no
* 2(6,4)  0 8 8 8 8 15 15 15 15 15 21 21  no
* 3(4,7)  0 8 8 8 8 15 15 15 15 15 21 21  yes 8
* 4(2,8)  0 8 8 8 8  8 14 14 14 14 14 14  yes 2 8-2=6
* 5(5,6)  0 0 0 0 6  6  6  6  6  6  6  6  yes
*/

void back_strace(int w[], int v[], int n, int c, int** dp)
{
	int bestV = 0;
	for (int i = 0; i < n; ++i)
	{
		if (dp[i][c] != dp[i+1][c])
		{
			// 选择了第i个物品
			cout << w[i] << " ";
			bestV += v[i];
			c -= w[i];
		}
	}

	// 单独处理最后一行（也就是最后一个物品）
	if (dp[n][c] > 0)
	{
		bestV += v[n];
		cout << w[n] << " ";
	}

	cout << endl;
	cout << "背包的最大价值是：" << bestV << endl;
}

void func_1()
{
	int w[] = { 8,6,4,2,5 };
	int v[] = { 6,4,7,8,6 };
	int n = sizeof(w) / sizeof(w[0]) - 1;
	int c = 12;

	// 定义dp数组记录子问题解
	int** dp = new int* [n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		dp[i] = new int[c + 1]();
	}

	// 先填写初始状态的值 填写dp数组的最后一行 物品n
	for (int j = 1; j <= c; ++j)
	{
		if (w[n] > j)  // 第n个物体的重量大于背包剩余容量
		{
			dp[n][j] = 0;
		}
		else  // 第n个物体的重量小于等于背包剩余容量
		{
			dp[n][j] = v[n];
		}
	}

	// 从 n-1 -> 0 行开始
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = 1; j <= c; ++j)
		{
			if (w[i] > j)  // 第i个物体无法装入背包
			{
				dp[i][j] = dp[i + 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i + 1][j], v[i] + dp[i + 1][j - w[i]]);
			}
		}
	}

	// 打印
	//for (int i = 0; i <= n; ++i)
	//{
	//	for (int j = 1; j <= c; ++j)
	//	{
	//		cout << dp[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	back_strace(w, v, n, c, dp);

	for (int i = 0; i < n + 1; ++i)
		delete[] dp[i];
	delete[] dp;
}

#if 0
int main()
{
	func_1();

	return 0;
}
#endif