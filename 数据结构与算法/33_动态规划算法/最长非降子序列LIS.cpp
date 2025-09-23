#include <iostream>

using namespace std;

/*
* LIS���⣺�����е���ǽ������������еĳ��� O(N^2)
* ���磺5 3 4 1 8 7 9
* 
* ���ؽⷨ����һ���õ����Ž⣬��Ч�ⷨ
* 
* 
* ״̬��
* dp[i] �Ե�i��Ԫ�ؽ�β�ķǽ������еĳ���
* 
* ״̬ת�Ʒ��̣�
* dp[0] = 1
* dp[1] = max{1, 1 + dp[0]} ar[0] < ar[1] = 1
* dp[2] = max{1, 1 + dp[1]} ar[1] < ar[2] = 2
* ...
* dp[i] = max{1, 1 + dp[j]} arr[j] <= arr[i]  j��Ԫ�غ�i��Ԫ�ز��ܹ��ɷǽ�������
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