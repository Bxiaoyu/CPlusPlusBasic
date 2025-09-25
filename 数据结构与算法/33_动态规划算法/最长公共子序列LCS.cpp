#include <iostream>
#include <string>

using namespace std;


/*
* LCS：求两个序列的最长公共子序列的长度
* helloworlr
*    hlweord
* 
* helloworl hlweord -> 情况一
* helloworlr hlweor -> 情况二
* 
* X:x1,x2...xn
* Y:y1,y2...ym
* 
* 状态转移方程：
* 如果xn == ym
* LCS(x[1...n], y[1...m]) = LCS(x[1...n-1], y[1...m-1]) + 1
* 如果 xn != ym
* LCS(x[1...n], y[1...m]) = max(LCS(x[1...n], y[1...m-1]), LCS(x[1...n-1], y[1...m]))
* 
* 状态：
* 给定的两个序列的LCS长度
* dp[n][m]  n-表示第一个串的长度 m-表示第二个串的长度 n行m列的元素值，记录的就是这两个串的LCS长度
*/

int cnt_ = 0;
string str1 = "helloworld";
string str2 = "hlweord";
int** dp = nullptr;
int** path = nullptr;  // 记录最长子序列

// 分治算法实现，会存在重复子问题
int lcs_1(string str1, int n, string str2, int m)
{
	if (n < 0 || m < 0)
	{
		return 0;
	}
	cnt_++;
	if (str1[n] == str2[m])
	{
		return lcs_1(str1, n - 1, str2, m - 1) + 1;
	}
	else
	{
		int l1 = lcs_1(str1, n, str2, m - 1);
		int l2 = lcs_1(str1, n - 1, str2, m);
		return max(l1, l2);
	}
}

void test_lcs_1()
{
	int l1 = str1.size();
	int l2 = str2.size();
	cnt_ = 0;
	cout << "LCS Length: " << lcs_1(str1, l1 - 1, str2, l2 - 1) << endl;
	cout << "cnt: " << cnt_ << endl;
}

// 动态规划实现，递归
int lcs_2(string str1, int n, string str2, int m)
{
	if (n < 0 || m < 0)
	{
		return 0;
	}

	if (dp[n][m] >= 0)  // 查表，查子问题的解是否被求解过
	{
		return dp[n][m];
	}

	cnt_++;

	if (str1[n] == str2[m])
	{
		dp[n][m] = lcs_2(str1, n - 1, str2, m - 1) + 1;
		path[n][m] = 1;  // n,m -> n-1, m-1 对角线
		return dp[n][m];
	}
	else
	{
		int l1 = lcs_2(str1, n, str2, m - 1);
		int l2 = lcs_2(str1, n - 1, str2, m);
		if (l1 >= l2)
		{
			dp[n][m] = l1;
			path[n][m] = 2;  // n,m -> n, m-1 左边
		}
		else
		{
			dp[n][m] = l2;
			path[n][m] = 3;  // n,m -> n-1, m 上方
		}

		return dp[n][m];
	}
}

// 动态规划实现，非递归
int lcs_3(string str1, int n, string str2, int m)
{
	for (int i = 1; i <= n+1; ++i)
	{
		for (int j = 1; j <= m+1; ++j)
		{
			if (str1[i-1] == str2[j-1])
			{
				dp[i][j] = 1 + dp[i - 1][j - 1];
				path[i][j] = 1;
			}
			else
			{
				int l1 = dp[i - 1][j];  // 上面
				int l2 = dp[i][j - 1];  // 左面
				if (l1 >= l2)
				{
					dp[i][j] = l1;
					path[i][j] = 3;
				}
				else
				{
					dp[i][j] = l2;
					path[i][j] = 2;
				}
			}
		}
	}

	return dp[n + 1][m + 1];
}

// 输出公共子序列
void back_trace(string str, int n, int m)
{
	if (n < 0 || m < 0)
	{
		return;
	}

	if (path[n][m] == 1)
	{
		back_trace(str, n - 1, m - 1);  // 走斜线
		cout << str[n];  // 回溯过程中再打印
	}
	else
	{
		if (path[n][m] == 2)
		{
			back_trace(str, n, m - 1);  // 向左
		}
		else  // path[n][m] == 3
		{
			back_trace(str, n - 1, m);  // 向上
		}
	}
}

void back_trace_2(string str, int n, int m)
{
	if (n <= 0 || m <= 0)
	{
		return;
	}

	if (path[n][m] == 1)
	{
		back_trace_2(str, n - 1, m - 1);  // 走斜线
		cout << str[n-1];  // 回溯过程中再打印
	}
	else
	{
		if (path[n][m] == 2)
		{
			back_trace_2(str, n, m - 1);  // 向左
		}
		else  // path[n][m] == 3
		{
			back_trace_2(str, n - 1, m);  // 向上
		}
	}
}

void test_lcs_2()
{
	int n = str1.size();
	int m = str2.size();
	dp = new int* [n];  // n行
	for (int i = 0; i < n; ++i)
	{
		dp[i] = new int[m];  // m列
		for (int j = 0; j < m; ++j)
		{
			dp[i][j] = -1;
		}
	}

	path = new int* [n];  // n行
	for (int i = 0; i < n; ++i)
	{
		path[i] = new int[m]();  // m列
	}

	cnt_ = 0;
	int res = lcs_2(str1, n - 1, str2, m - 1);
	cout << "lec length: " << res << endl;
	cout << "cnt: " << cnt_ << endl;

	//for (int i = 0; i < n; ++i)
	//{
	//	for (int j = 0; j < m; ++j)
	//	{
	//		cout << path[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	back_trace(str1, n - 1, m - 1);

	for (int i = 0; i < n; i++)
	{
		delete[] dp[i];  // 释放每个子数组
	}
	delete[] dp;  // 释放指针数组本身

	for (int i = 0; i < n; i++)
	{
		delete[] path[i];
	}
	delete[] path;
}

void test_lcs_3()
{
	int n = str1.size();
	int m = str2.size();
	dp = new int* [n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		dp[i] = new int[m + 1];
		for (int j = 0; j < m + 1; ++j)
		{
			dp[i][j] = 0;
		}
	}

	path = new int* [n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		path[i] = new int[m + 1]();
	}

	int size = lcs_3(str1, n-1, str2, m-1);
	cout << "lcs length: " << size << endl;
	cout << "cnt: " << cnt_ << endl;

	back_trace_2(str1, n, m);

	for (int i = 0; i < n + 1; ++i)
		delete[] dp[i];
	delete[] dp;

	for (int i = 0; i < m + 1; ++i)
		delete[] path[i];
	delete[] path;
}

#if 0
int main()
{
	//test_lcs_1();
	//test_lcs_2();
	test_lcs_3();
	return 0;
}
#endif