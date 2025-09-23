#include <iostream>

using namespace std;

/*
* LIS问题：求序列的最长非降（升序）子序列的长度 O(N^2)
* 例如：5 3 4 1 8 7 9
* 
* 朴素解法：不一定得到最优解，无效解法
* 
* 
* 状态：
* dp[i] 以第i个元素结尾的非降子序列的长度
* 
* 状态转移方程：
* dp[0] = 1
* dp[1] = max{1, 1 + dp[0]} ar[0] < ar[1] = 1
* dp[2] = max{1, 1 + dp[1]} ar[1] < ar[2] = 2
* ...
* dp[i] = max{1, 1 + dp[j]} arr[j] <= arr[i]  j号元素和i号元素才能构成非降子序列
*/

void max_asc_sub_segment()
{
	int arr[] = { 5,3,4,1,8,6,7,10 };
	const int n = sizeof(arr) / sizeof(arr[0]);
	int dp[n] = { 0 };
	int max_len = 0;

	for (int i = 0; i < n; ++i)
	{
		dp[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (arr[j] <= arr[i] && 1 + dp[j] > dp[i])
			{
				dp[i] = 1 + dp[j];
			}
		}

		if (dp[i] > max_len)
		{
			max_len = dp[i];
		}
	}

	cout << "max_len: " << max_len << endl;
}

#if 0
int main()
{
	max_asc_sub_segment();
	return 0;
}
#endif