#include <iostream>


using namespace std;


/*
* 硬币选择问题：有1、3、5分面额的硬币，给定一个面值，问组合成给定面值所需的最少硬币数量是多少？
* 11:	1+(10)							3+(8)						5+(6)
* 10:	1+(9) 3+(7) 5+(5)
*									8:	1+(7) 3+(5) 5+(3)
*																6: 1+(5) 3+(3) 5+(1)
* 
* 子问题的状态（最优解）：(9)组成价值9需要的硬币的最少数量
* dp[i]：组成面值i需要的硬币的最少数量
*/

// 参数n表示面值，返回值表示组成面值n所需的最少硬币数量
const int n = 11;
int dp[n + 1] = { 0 };  // dp[n]：组成价值n所需要的硬币最少数量
int cnt = 0;  // 测试

// 用分治算法求解
int func1(int n)
{
	if (dp[n] > 0)  // dp[n]这个子问题已经被求解过
	{
		cnt++;
		return dp[n];
	}
	if (n == 1 || n == 3 || n == 5)
	{
		dp[n] = 1;  // 代表了一个子问题最优解的性质（状态）
		return 1;
	}
	else if (n == 2 || n == 4)
	{
		dp[n] = 2;
		return 2;
	}
	else
	{
		int n1 = func1(n - 1) + 1;  // 选择了1分硬币
		int n3 = func1(n - 3) + 1;  // 选择了3分硬币
		int n5 = func1(n - 5) + 1;  // 选择了5分硬币
		dp[n] = std::min({ n1,n3,n5 });
		return dp[n];
	}
}


/*
* 动态规划
* 问题的状态: dp[i]表示组成面值i所需要的最少的硬币数量
* 状态转移方程：
* dp[0] = 0
* dp[1] = 1 + dp[1-1] = 1
* dp[2] = 1 + dp[2-1] = 1 + dp[1] = 1 + 1 = 2
* dp[3]:
*		1 + dp[3-1] = 1 + dp[2] = 1 + 2 = 3  选择了3个1分硬币
*		3 + dp[3-3] = 1 + dp[0] = 1 + 0 = 1  选择了1个3分硬币
* 
* dp[4]:
*		1 + dp[4-1] = 1 + dp[3] = 1 + 1 = 2  1,3 选择了一个1分和一个3分
*		1 + dp[4-3] = 1 + dp[1] = 1 + 1 = 2  3,1 选择了一个3分和一个1分
* 
* dp[5]:
*		1 + dp[5 - 1] = 1 + dp[4] = 1 + 2 = 3  1,1,3 选择两个1分和一个3分
*		1 + dp[5 - 3] = 1 + dp[2] = 1 + 2 = 3  3,1,1 选择一个3分和两个1分
*		1 + dp[5 - 5] = 1 + dp[0] = 1 + 0 = 1  5 选择一个5分
* 
* 从以上理论推导，得到以下状态转移方程：
* dp[i] = min(1 + dp[i-Vj])  i-表示面值，Vj-表示第i个硬币的面额 条件 i >= Vj
*/

void select_coin()
{
	int v[] = { 1,3,5 };
	int len = sizeof(v) / sizeof(v[0]);
	int c = 11;
	int* dp = new int[c + 1]();  // dp[c] dp[0] = 0
	for (int i = 1; i <= c; i++)
	{
		dp[i] = i;  // 表示初始全部由1分硬币构成
		for (int j = 0; j < len; j++)
		{
			if (i >= v[j] && (1 + dp[i-v[j]]) < dp[i])
			{
				dp[i] = 1 + dp[i - v[j]];
			}
		}
	}

	cout << "dp[n]：" << dp[c];
	delete[] dp;
}

#if 0
int main()
{
	//int res = func1(n);
	//cout << "dp[n]：" << res << endl;
	//cout << "cnt：" << cnt << endl;
	select_coin();
	return 0;
}
#endif