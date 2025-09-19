#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


double middle_value(vector<int>& nums1, int len1, vector<int>& nums2, int len2)
{
	if (len1 > len2)  // �ڶ������������ʵ�i��j
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
	while (begin <= end)  // �����������㷨˼�룬����ʱ���ҵ�i+j=k
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
	if (i == 0)  // nums1����̫�̣�������Ԫ�ض��ܴ���ô��λ���϶���nums2���������
	{
		left = nums2[j - 1];
	}
	else if (j == 0)  // nums2����̫�̣���ô��λ���϶���nums1�������
	{
		left = nums1[i - 1];
	}
	else
	{
		left = max(nums1[i - 1], nums2[j - 1]);
	}

	int right = 0;
	if (i == len1)  // nums1����Ԫ��̫�٣���ֵ����С����λ���϶���nums2������
	{
		right = nums2[j];
	}
	else if (j == len2)  // nums2����Ԫ��̫�٣���λ���϶���nums1������
	{
		right = nums1[i];
	}
	else
	{
		right = min(nums1[i], nums2[j]);
	}

	// �ҵ��˺��ʵ�ֵ
	if ((len1 + len2) % 2 == 0)  // ż������
	{
		return (left + right) * 1.0 / 2;
	}
	else  // ��������
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