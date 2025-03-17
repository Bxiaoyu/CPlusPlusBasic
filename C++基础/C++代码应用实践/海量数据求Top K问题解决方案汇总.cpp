#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

/*
* ����������Top K������
* 1�������/��С��ǰK��Ԫ��
* 2�������/��С�ĵ�K��Ԫ��
* 
* 
* �ⷨ1�������/С���ѣ����ȼ����У�
* 
* 1000����������ֵǰ10���Ԫ��
* ����ǰ10����������һ��С���ѣ���Сֵ���ڶѶ�����Ȼ�����ʣ�µ���������������ȶѶ�Ԫ�ش���ôɾ���Ѷ�Ԫ��
* ��������ѣ�����������������С�������ŵľ���ֵ����ǰʮ��Ԫ���ˣ�����ҵ��ǵ�KС�ģ�����ѶѶ������ߵ�K��
* ��С���ѶѶ�����ֻ����ʶѶ�һ��Ԫ��
* 
* ����� -����Top kС��
* С���� -����Top k���
* 
* �ⷨ2�����ŷָ����һ����˵Ч�ʸ��ߣ�
* 
* �������ŷָ�����ܹ���O(lgn)ʱ���ڣ���С�ڻ�׼����������������ߣ��Ѵ��ڻ�׼���������������ұߣ���׼����index���Ϳ�����Ϊ
* �ǵڣ�index+1��С�������ˣ�[0,index]����ǰindex+1С��������
*/

/*
* С����
*/
void test_minheap()
{
	// ��������Ԫ��ֵ����ǰʮ����
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}

	// �ȶ���С����
	priority_queue<int, vector<int>, greater<int>> minHeap;
	// ����С���ѷ���10��Ԫ��
	int k = 0;
	for (;k < 10;++k)
	{
		minHeap.push(vec[k]);
	}

	// ����ʣ�µ���������������ȶѶ�Ԫ�ش���ôɾ���Ѷ�Ԫ��
	// ��������ѣ�����������������С�������ŵľ���ֵ����ǰʮ��Ԫ���ˣ�����ҵ��ǵ�KС�ģ�����ѶѶ������ߵ�K��
    //��С���ѶѶ�����ֻ����ʶѶ�һ��Ԫ��
	for (;k < vec.size();++k)
	{
		if (minHeap.top() < vec[k])
		{
			minHeap.pop();
			minHeap.push(vec[k]);
		}
	}

	cout << "��10С��Ԫ�أ�" << minHeap.top() << endl;

	cout << "ǰ10���Ԫ�أ�";
	// ��ӡ���
	while (!minHeap.empty())
	{
		cout << minHeap.top() << " ";
		minHeap.pop();
	}
	cout << endl;
}

/*
* ���ŷָ�
*/
int partation(vector<int>& arr, int i, int j)
{
	int k = arr[i];
	while (i < j)
	{
		while (i < j && arr[j] >= k)
		{
			j--;
		}
		if (i < j)
		{
			arr[i++] = arr[j];
		}
		while (i < j && arr[i] < k)
		{
			i++;
		}
		if (i < j)
		{
			arr[j--] = arr[i];
		}
	}

	arr[i] = k;
	return i;
}

int selectNoK(vector<int>& arr, int i, int j, int k)
{
	int pos = partation(arr, i, j);
	if (pos == k-1)
	{
		return pos;
	}
	else if (pos < k - 1)
	{
		return selectNoK(arr, pos + 1, j, k);
	}
	else
	{
		return selectNoK(arr, i, pos - 1, k);
	}
}

void test_quick_sort_split()
{
	// �������е�10С��Ԫ��ֵ��ǰ10С
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}

	// ���صľ��ǵ�ʮС��Ԫ�ص�ֵ
	int index = selectNoK(vec, 0, vec.size() - 1, 10);
	cout << "��10С��Ԫ�أ�" << vec[index] << endl;
	cout << "ǰ10С��Ԫ�أ�";
	for (int i = 0; i <= index; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

/*
* ���غ�top k�ۺ�Ӧ��
* 
* ��һ�������У��ҳ��ظ���������ǰ10��
* 
* ������ݺܴ��ڴ������ƣ���Ҫ�÷���˼��ָ����ݵ���ͬ�ļ�
*/
void test_top_k()
{
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}

	unordered_map<int, int> numMap;
	for (auto val : vec)
	{
		numMap[val]++;  // ���val�����ڣ���ֱ�Ӳ���һ��
	}

	// �ȶ���С����
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto& a, auto& b)->bool
		{
			return a.second > b.second;  // �Զ���С����Ԫ�صıȽϷ�ʽ
		});

	// �����ѷ�k������
	int k = 0;
	auto it = numMap.begin();
	// �ȴ�map���ж�ȡ10�����ݵ�С�����У�����top10��С���ѣ���СԪ���ڶѶ�
	for (;it != numMap.end() && k < 10;++it, ++k)
	{
		minheap.push(*it);
	}

	// ��k+1��ĩβ��Ԫ�ؽ��б������ͶѶ�Ԫ�ؽ��бȽ�
	for (;it != numMap.end();++it)
	{
		if (it->second > minheap.top().second)
		{
			minheap.pop();
			minheap.push(*it);
		}
	}

	// ����ʣ�µľ����ظ���������ǰk��
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << ":" << pair.second << endl;
		minheap.pop();
	}
}

#if 0
int main()
{
	//test_minheap();
	//test_quick_sort_split();
	test_top_k();
	return 0;
}
#endif