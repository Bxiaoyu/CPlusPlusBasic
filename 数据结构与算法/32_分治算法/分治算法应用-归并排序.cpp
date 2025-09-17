#include <iostream>
#include <vector>

using namespace std;


/*
* �����㷨Ӧ�� - �鲢����
*/

void merge(vector<int>& vec, int low, int high, int mid)
{
	// �������ĸ����ռ䣬�洢�ϲ����������������
	vector<int> tmp;
	tmp.reserve(high - low + 1);
	int l = low;
	int r = mid + 1;

	while (l <= mid && r <= high)
	{
		if (vec[l] < vec[r])
		{
			tmp.push_back(vec[l++]);
		}
		else
		{
			tmp.push_back(vec[r++]);
		}
	}

	while (l <= mid)
	{
		tmp.push_back(vec[l++]);
	}

	while (r <= high)
	{
		tmp.push_back(vec[r++]);
	}

	// tmp�����Ԫ�� -��vec������
	for (int i = low; i <= high; ++i)
	{
		vec[i] = tmp[i - low];
	}
}

void merge_sort(vector<int>& vec, int i, int j)
{
	if (i >= j)  // �����⻮�ֵ�һ��Ԫ�ص�ʱ�򣬾ʹ���������Ľ�����֪����
	{
		return;
	}

	int mid = (i + j) / 2;
	// �Ȼ��������⣬���������ģ
	merge_sort(vec, i, mid);
	merge_sort(vec, mid + 1, j);

	// ���ϻ��ݣ����ݹ����У��ϲ�������Ľ�
	merge(vec, i, j, mid);  // [i, mid] [mid+1, j]
}

#if 0
int main()
{
	vector<int> vec;
	for (int i = 0; i < 11; ++i)
		vec.push_back(rand() % 100);

	for (const auto& val : vec)
		cout << val << " ";
	cout << endl;

	merge_sort(vec, 0, vec.size() - 1);
	for (const auto& val : vec)
		cout << val << " ";
	cout << endl;

	return 0;
}
#endif