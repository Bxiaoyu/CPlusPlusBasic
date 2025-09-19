#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


double middle_value(vector<int>& nums1, int len1, vector<int>& nums2, int len2)
{
	if (len1 > len2)  // 在短数组中求解合适的i和j
	{
		middle_value(nums2, len2, nums1, len1);
	}

	if (len1 == 0)
	{
		int k = (len2 - 1) / 2;
		if (len2 % 2 == 0)
		{
			return (nums2[k] + nums2[k + 1]) * 1.0 / 2;
		}
		else
		{
			return nums2[k];
		}
	}

	int i = 0;
	int j = 0;
	int begin = 0;
	int end = len1;
	int k = (len1 + len2 + 1) / 2;  // 7 / 2 = 3 0000000
	while (begin <= end)  // 二分搜索的算法思想，对数时间找到i+j=k
	{
		i = (begin + end) / 2;
		j = k - i;
		if (i > 0 && j < len2 && nums1[i - 1] > nums2[j])
		{
			end = i - 1;
		}
		else if (j > 0 && i < len1 && nums2[j-1] > nums1[i])
		{
			begin = i + 1;
		}
		else
		{
			break;  // arr[i-1] < brr[j] && brr[j-1] < arr[i]
		}
	}

	int left = 0;
	if (i == 0)  // nums1数组太短，且数组元素都很大，那么中位数肯定在nums2这个数组中
	{
		left = nums2[j - 1];
	}
	else if (j == 0)  // nums2数组太短，那么中位数肯定在nums1这个数组
	{
		left = nums1[i - 1];
	}
	else
	{
		left = max(nums1[i - 1], nums2[j - 1]);
	}

	int right = 0;
	if (i == len1)  // nums1数组元素太少，且值都很小，中位数肯定在nums2数组中
	{
		right = nums2[j];
	}
	else if (j == len2)  // nums2数组元素太少，中位数肯定在nums1数组中
	{
		right = nums1[i];
	}
	else
	{
		right = min(nums1[i], nums2[j]);
	}

	// 找到了合适的值
	if ((len1 + len2) % 2 == 0)  // 偶数长度
	{
		return (left + right) * 1.0 / 2;
	}
	else  // 奇数长度
	{
		return left;
	}
}


int main()
{
	vector<int> vec1;
	vector<int> vec2;

	for (int i = 0; i < 10; ++i)
	{
		vec1.push_back(rand() % 100);
	}

	for (int i = 0; i < 6; ++i)
	{
		vec2.push_back(rand() % 100);
	}

	vector<int> vec = vec1;
	for (int v : vec2)
	{
		vec.push_back(v);
	}
	sort(vec.begin(), vec.end());
	for (int v : vec)
		cout << v << " ";
	cout << endl;

	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	double middle = middle_value(vec1, vec1.size(), vec2, vec2.size());
	cout << "middle: " << middle << endl;

	return 0;
}