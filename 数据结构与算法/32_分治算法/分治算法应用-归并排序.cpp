#include <iostream>
#include <vector>

using namespace std;


/*
* 分治算法应用 - 归并排序
*/

void merge(vector<int>& vec, int low, int high, int mid)
{
	// 定义额外的辅助空间，存储合并子问题的有序数组
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

	// tmp数组的元素 -》vec数组中
	for (int i = low; i <= high; ++i)
	{
		vec[i] = tmp[i - low];
	}
}

void merge_sort(vector<int>& vec, int i, int j)
{
	if (i >= j)  // 子问题划分到一个元素的时候，就代表子问题的解是已知的了
	{
		return;
	}

	int mid = (i + j) / 2;
	// 先划分子问题，降低问题规模
	merge_sort(vec, i, mid);
	merge_sort(vec, mid + 1, j);

	// 向上回溯，回溯过程中，合并子问题的解
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