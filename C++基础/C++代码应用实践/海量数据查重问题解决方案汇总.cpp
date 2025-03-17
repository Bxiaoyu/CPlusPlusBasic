#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

/*
* �������ݲ���/ȥ�غ���Top K������
* �������ݵĲ������⣺
* 1����ϣ�� 50�ڣ�5G����������20G+20G�� 10�ڣ�1G��
* 2������˼��
* 3����¡������
* 4������ַ������ͣ�TrieTree�ֵ�����ǰ׺����
*/

/*
* 1�����������ݲ���˼��
*/
void test_1()
{
	const int SIZE = 10000;
	int arr[SIZE] = { 0 };
	for (int i = 0; i < SIZE; ++i)
	{
		arr[i] = rand();
	}

	// ������SIZE�������У��ҳ�˭�ظ��ˣ�����ͳ���ظ�
	unordered_map<int, int> _map;
	for (int val : arr)
	{
		_map[val]++;
	}

	for (auto pair : _map)
	{
		if (pair.second > 1)
		{
			cout << "���֣�" << pair.first << " �ظ�������" << pair.second << endl;
		}
	}
}

/*
* 2����һ���ļ����д���������50�ڸ������ڴ�����400M���ҳ��ļ��е��ظ�Ԫ�غʹ���
* 50�� 5G * 4 = 20G * 2 = 40G
* ���������󣬲��÷���˼�룺
* ���ļ�����ΪС�ļ���ʹ��ÿһ��С�ļ��ܹ����ص��ڴ浱�У������Ӧ���ظ�Ԫ�أ��ѽ��д��һ���洢�ظ�Ԫ�ص��ļ�
* 
* ���ļ�-��С�ļ�������40G/400M��
* data0.txt
* data1.txt
* ...
* data126.txt
* 
* �������ļ���Ԫ�أ���ÿһ��Ԫ�ظ��ݹ�ϣӳ�亯�����ŵ���Ӧ��ŵ�С�ļ�����
* data % 127 = file_index
* 
* ֵ��ͬ�ģ�ͨ��һ���Ĺ�ϣӳ�亯�����϶�����ͬһ��С�ļ�����
*/
void test_2()
{
#if 0
	// λ�п��ٻ�ȡ�������С�����ݹ�ģ
	FILE* pf1 = fopen("data.dat", "wb");
	for (int i = 0; i < 20000; ++i)
	{
		int data = rand();
		if (data < 0)
		{
			cout << data << endl;
		}
		fwrite(&data, 4, 1, pf1);
	}
	fclose(pf1);
#endif

	// ��Դ����
	FILE* pf = fopen("data.dat", "rb");
	if (pf == nullptr)
	{
		return;
	}

	const int FILE_NO = 11;
	FILE* pfile[FILE_NO] = { nullptr };
	for (int i = 0; i < FILE_NO; ++i)
	{
		char filename[20];
		sprintf(filename, "data%d.dat", i + 1);
		pfile[i] = fopen(filename, "wb+");
	}

	// ��ϣӳ�䣬�Ѵ��ļ��е�����ӳ�䵽����С�ļ�����
	int data;
	while (fread(&data, 4, 1, pf) > 0)
	{
		int findex = data % FILE_NO;
		fwrite(&data, 4, 1, pfile[findex]);
	}

	// ����һ����ʽ��ϣ��
	unordered_map<int, int> numMap;
	// �ȶ���һ��С����
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto& a, auto& b)->bool {
		return a.second > b.second;  // �Զ���С����Ԫ�رȽϷ�ʽ
		});

	// �ֶ����С�ļ���top10������ݣ���������ս��
	for (int i = 0; i < FILE_NO; ++i)
	{
		// �ָ�С�ļ����ļ�ָ�뵽��ʼλ��
		fseek(pfile[i], 0, SEEK_SET);

		while (fread(&data, 4, 1, pfile[i]) > 0)
		{
			numMap[data]++;
		}

		int k = 0;
		auto it = numMap.begin();
		// ������ǿյģ������ѷ�10������
		if (minheap.empty())
		{
			// ��map���ж�10�����ݵ�С���ѣ�����top 10��С���ѣ���С��Ԫ���ڶѶ�
			for (;it != numMap.end() && k < 10;++it, ++k)
			{
				minheap.push(*it);
			}
		}

		// ��k+1��ĩβ��Ԫ�ؽ��б������ͶѶ�Ԫ�ؽ��жԱ�
		for (;it != numMap.end();++it)
		{
			// ���map���е�ǰԪ���ظ��������ڶѶ�Ԫ�ص��ظ����������滻
			if (it->second > minheap.top().second)
			{
				minheap.pop();
				minheap.push(*it);
			}
		}

		// ��չ�ϣ��������һ��С�ļ�������ͳ��
		numMap.clear();
	}

	// ����ʣ��ľ����ظ���������ǰk��
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << ":" << pair.second << endl;
		minheap.pop();
	}
}


/*
* 3��
* a��b�����ļ������涼��10�ڸ��������ڴ�����400M�����a,b�����ļ��е��ظ�Ԫ������Щ��
* 
* 10�� -��1G * 4 = 4G*2 = 8G/400M = 27��С�ļ�
* a-��ȫ�������ڴ��У��洢����ϣ��
* b-����b�ļ������ݣ����ڴ��ϣ���в�ѯ
* 
* ��a��b�����ļ������ֳɸ�����ȵ�һϵ�У�27��С�ļ�������˼�룩
* a1.txt b1.txt
* a2.txt b2.txt
* a3.txt b3.txt
* ...
* a26.txt b26.txt
* 
* ��a�ļ��ж�ȡ���ݣ�ͨ�� ����%27 = file_index
* ��b�ļ��ж�ȡ���ݣ�ͨ�� ����%27 = file_index
* 
* a��b�����ļ��У�������ͬ��Ԫ�أ����й�ϣӳ���Ժ󣬿϶�����ͬ��ŵ�С�ļ���
* 
* ����a1��b1...ֱ��a26��b26
*/

#if 0
int main()
{
	test_2();
	return 0;
}
#endif