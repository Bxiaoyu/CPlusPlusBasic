#include <iostream>
#include <vector>

using namespace std;

/*
* ������ʧЧ����
* 1��������Ϊʲô��ʧЧ��
* - ����������erase�����󣬵�ǰλ�õ�����ĩβԪ�ص����е�����ȫ��ʧЧ��
* - ����������insert�����󣬵�ǰλ�õ�����ĩβԪ�ص����е�����ȫ��ʧЧ��
* 
* ��������Ȼ��Ч    -      ������ȫ��ʧЧ
* ��Ԫ��  ---- ����/ɾ���� ---- ĩβԪ��
* 
* - ��insert������˵��������������ڴ����ݣ���ԭ�����������е�����ȫ��ʧЧ��
* 
* - ��ͬ�����ĵ������ǲ��ܽ��бȽ�����ģ�
* 
* 2��������ʧЧ�Ժ󣬸���ô�����
* - �Բ���/ɾ����ĵ��������и��²���
*/
#if 0
int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

#if 1
	auto it = vec.begin();
	for (;it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			// ����ĵ������ڵ�һ��insert�󣬾�ʧЧ��
			it = vec.insert(it, *it - 1);  // ���µ��������ʧЧ����
			++it;
			// break;
		}
	}
#endif

#if 0
	// ��vector����������ż��ɾ��
	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			// ������ʧЧ���⣬��һ�ε���erase�󣬵�����it��ʧЧ��
			// ͨ�����µ����������ʧЧ����
			it = vec.erase(it);  // ɾ����ͬʱ���µ�����
			//break;
		}
		else
		{
			++it;
		}
	}
#endif

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif