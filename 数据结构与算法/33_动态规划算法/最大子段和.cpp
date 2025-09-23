#include <iostream>


using namespace std;


/*
* ����Ӷκ����⣺
*	����n��������ɵ����У�����ӶκͶ���Ϊ���������Ӷκ͵����ֵ��������������Ϊ����ʱ���Ϊ0��
*	���磬����(-2,11,-4,13,-5,-2)������Ӷκ�Ϊ20��
* 
* ״̬��
* dp[i] �Ե�i��Ԫ�ؽ�β���Ӷκ͵�ֵ
* 
* ״̬ת�Ʒ��̣�
* dp[0] = val < 0 ? 0 : val
* dp[1] = ar[1] + dp[0] = 11
* dp[2] = ar[2] + dp[1] = -4 + 11 = 7
* dp[3] = ar[3] + dp[2] = 13 + 7 = 20
* dp[4] = ar[4] + dp[3] = -5 + 20 = 15
* dp[5] = ar[5] + dp[4] = -2 + 15 = 13
* 
* dp[i] = ar[i] + dp[i-1] (i > 0) i == 0�Ӷκ���Ϊ����֪��
*/


void sum_max_sub_segment()
{
	int vec[] = { -2,11,-4,13,-5,-2 };
	const int n = sizeof(vec) / sizeof(vec[0]);
	int dp[n] = { 0 };
	dp[0] = vec[0] < 0 ? 0 : vec[0];

	int max_sum = dp[0];
	for (int i = 1; i < n; ++i)
	{
		dp[i] = vec[i] + dp[i - 1];
		if (dp[i] < 0)
			dp[i] = 0;

		if (max_sum < dp[i])
			max_sum = dp[i];
	}

	cout << "dp[n]��" << max_sum << endl;
}

#if 0
int main()
{
	sum_max_sub_segment();

	return 0;
}
#endif