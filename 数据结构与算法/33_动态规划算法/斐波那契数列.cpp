#include <iostream>

using namespace std;

// 斐波那契数列为1、1、2、3、5、8、13、21、34……此数列从第3项开始,每一项都等于前两项之和
// 表达式：F[n]=F[n-1]+F[n-2](n&gt;=2,F[0]=1,F[1]=1)
// 用分治思想实现斐波那契数列
// 递归实现
int fibonacci_1(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}

	return fibonacci_1(n - 1) + fibonacci_1(n - 2);
}

/*
* 用动态规划来实现
* 递归实现
* 怎么描述子问题最优解的性质 《-》问题的状态
* dp[i]：斐波那契数列中第i个数字的值
*/
int fibonacci_2(int n, int dp[])
{
	if (dp[n] > 0)  // 说明子问题n之前被求解过了
	{
		return dp[n];
	}

	if (n == 1 || n == 2)
	{
		dp[n] = 1;
		return 1;
	}
	else
	{
		dp[n] = fibonacci_2(n - 1, dp) + fibonacci_2(n - 2, dp);
		return dp[n];
	}
}

/*
* 非递归实现
* 状态：dp[i] 斐波那契数列中的第i个数字的值
* 状态转移方程：
* dp[1] = 1
* dp[2] = 1
* dp[3] = dp[3-1] + dp[3-2] = dp[2] + dp[1] = 2
* dp[i] = dp[i-1] + dp[i-2]  i > 2
*/

void fibonacci()
{
	int n = 10;
	int* dp = new int[n + 1]();
	dp[1] = 1;
	dp[2] = 1;
	for (int i = 3; i <= n; i++)
	{
		dp[i] = dp[i-1] + dp[i-2];
	}

	cout << "dp[n]: " << dp[n] << endl;
	delete[] dp;
}

#if 0
int main()
{
	//int n = 5;
	//cout << fibonacci_1(n) << endl;
	//int* dp = new int[n + 1]();
	//cout << fibonacci_2(n, dp) << endl;
	//delete[] dp;

	fibonacci();

	return 0;
}
#endif