#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
* 分治算法思想应用 - 快排算法，快排求topK
*/

int partation(vector<int>& vec, int i, int j)
{
	int val = vec[i];
	int left = i;
	int right = j;

	while (left < right)
	{
		while (left < right && vec[right] >= val)  // 右 - 左，找第一个比val小的
		{
			right--;
		}

		if (left < right)
		{
			vec[left++] = vec[right];
		}

		while (left < right && vec[left] <= val)  // 左 - 右，找第一个比val大的
		{
			left++;
		}

		if (left < right)
		{
			vec[right--] = vec[left];
		}
	}

	vec[left] = val;  // 放置基准数
	return left;      // 返回基准数的下标
}

void quick_sort(vector<int>& vec, int i, int j)
{
	if (i >= j)
	{
		return;
	}

	int pos = partation(vec, i, j);
	quick_sort(vec, i, pos - 1);
	quick_sort(vec, pos + 1, j);
}

int max_select_topK(vector<int>& vec, int i, int j, int k)
{
	int pos = partation(vec, i, j);  // pos表示基准数的位置
	if (pos == vec.size() - k)  // 基准数的位置和topk的k值相等
	{
		return pos;
	}
	else if (pos < vec.size() - k)  // topk应该在基准数的右边
	{
		return max_select_topK(vec, pos + 1, j, k);
	}
	else
	{
		return max_select_topK(vec, i, pos - 1, k);
	}
}

int min_select_topK(vector<int>& vec, int i, int j, int k)
{
	int pos = partation(vec, i, j);  // pos表示基准数的位置
	if (pos == k - 1)  // 基准数的位置和topk的k值相等
	{
		return pos;
	}
	else if (pos < k - 1)  // topk应该在基准数的右边
	{
		return min_select_topK(vec, pos + 1, j, k);
	}
	else
	{
		return min_select_topK(vec, i, pos - 1, k);
	}
}

void test_quick_sort()
{
	vector<int> vec;
	for (int i = 0; i < 11; ++i)
	{
		vec.push_back(rand() % 100);
	}

	for (const auto& item : vec)
		cout << item << " ";
	cout << endl;

	quick_sort(vec, 0, vec.size() - 1);

	for (const auto& item : vec)
		cout << item << " ";
	cout << endl;
}

void test_max_select_topK()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100);
	}

	// 求top 10的元素
	//int pos = max_select_topK(vec, 0, vec.size() - 1, 4);
	//cout << "第topK大的: " << vec[pos] << endl;
	//cout << "前topK大的：";
	//for (int i = pos; i < vec.size(); ++i)
	//	cout << vec[i] << " ";
	//cout << endl;

	int pos = min_select_topK(vec, 0, vec.size() - 1, 4);
	cout << "第topK小的：" << vec[pos] << endl;
	cout << "前topK大的：";
	for (int i = 0; i <= pos; ++i)
		cout << vec[i] << " ";
	cout << endl;

	sort(vec.begin(), vec.end());
	for (const auto& v : vec)
		cout << v << " ";
	cout << endl;
}

#if 0
int main()
{
	test_max_select_topK();
	return 0;
}
#endif