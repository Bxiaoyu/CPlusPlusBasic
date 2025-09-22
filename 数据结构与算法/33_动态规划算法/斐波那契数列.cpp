#include <iostream>

using namespace std;

// 쳲���������Ϊ1��1��2��3��5��8��13��21��34���������дӵ�3�ʼ,ÿһ�����ǰ����֮��
// ���ʽ��F[n]=F[n-1]+F[n-2](n&gt;=2,F[0]=1,F[1]=1)
// �÷���˼��ʵ��쳲���������
// �ݹ�ʵ��
int fibonacci_1(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}

	return fibonacci_1(n - 1) + fibonacci_1(n - 2);
}

/*
* �ö�̬�滮��ʵ��
* �ݹ�ʵ��
* ��ô�������������Ž������ ��-�������״̬
* dp[i]��쳲����������е�i�����ֵ�ֵ
*/
int fibonacci_2(int n, int dp[])
{
	if (dp[n] > 0)  // ˵��������n֮ǰ��������
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
* �ǵݹ�ʵ��
* ״̬��dp[i] 쳲����������еĵ�i�����ֵ�ֵ
* ״̬ת�Ʒ��̣�
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