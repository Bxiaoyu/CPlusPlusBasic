#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
* �����㷨˼��Ӧ�� - �����㷨��������topK
*/

int partation(vector<int>& vec, int i, int j)
{
	int val = vec[i];
	int left = i;
	int right = j;

	while (left < right)
	{
		while (left < right && vec[right] >= val)  // �� - ���ҵ�һ����valС��
		{
			right--;
		}

		if (left < right)
		{
			vec[left++] = vec[right];
		}

		while (left < right && vec[left] <= val)  // �� - �ң��ҵ�һ����val���
		{
			left++;
		}

		if (left < right)
		{
			vec[right--] = vec[left];
		}
	}

	vec[left] = val;  // ���û�׼��
	return left;      // ���ػ�׼�����±�
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
	int pos = partation(vec, i, j);  // pos��ʾ��׼����λ��
	if (pos == vec.size() - k)  // ��׼����λ�ú�topk��kֵ���
	{
		return pos;
	}
	else if (pos < vec.size() - k)  // topkӦ���ڻ�׼�����ұ�
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
	int pos = partation(vec, i, j);  // pos��ʾ��׼����λ��
	if (pos == k - 1)  // ��׼����λ�ú�topk��kֵ���
	{
		return pos;
	}
	else if (pos < k - 1)  // topkӦ���ڻ�׼�����ұ�
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

	// ��top 10��Ԫ��
	//int pos = max_select_topK(vec, 0, vec.size() - 1, 4);
	//cout << "��topK���: " << vec[pos] << endl;
	//cout << "ǰtopK��ģ�";
	//for (int i = pos; i < vec.size(); ++i)
	//	cout << vec[i] << " ";
	//cout << endl;

	int pos = min_select_topK(vec, 0, vec.size() - 1, 4);
	cout << "��topKС�ģ�" << vec[pos] << endl;
	cout << "ǰtopK��ģ�";
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