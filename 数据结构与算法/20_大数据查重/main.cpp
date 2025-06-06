// 20_�����ݲ���.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <vector>
#include <unordered_set> 
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

/*
���ص������������

�������ļ��ֱ���a��b��������˺ܶ�ip��ַ(url��ַ��email��ַ)�������ҳ��������ļ��ظ���ip���������

==> ��a�ļ������е�ip�����һ����ϣ���У�Ȼ�����α����ļ�b�����ip��ÿ
����һ��ip���ڹ�ϣ��������һ�£��ѵ��ģ����������ļ��ظ���ip�����
    �õ��˹�ϣ��Ĳ�ѯO(1)

�������ļ��ֱ���a��b�����Դ����Լ1����ip��ַ��ÿ��ip��ַ��4���ֽ������ڴ�ʹ��100M�����ҳ��������ļ����ظ���ip��ַ�����

*/

int main()
{
    string src = "jjhfgiyuhrtytrs";
    // �ҳ�����һ��û���ظ����ֹ����ַ�
    unordered_map<int, int> m;
    for (auto ch : src)
    {
        m[ch]++;
    }

    for (char ch : src)
    {
        if (m[ch] == 1)
        {
            cout << "��һ��û���ظ����ֹ����ַ��ǣ�" << ch << endl;
            break;
        }
    }

    cout << "�����ַ����ظ����ֹ�" << endl;

    return 0;
}

#if 0
int main()
{
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }

    // �ҵ�һ�������ظ�������
    // �������ظ����ֵ�����unordered_multiset
    unordered_set<int> s1;
    for (auto key : vec)
    {
        auto it = s1.find(key);
        if (it == s1.end())
        {
            s1.insert(key);
        }
        else
        {
            cout << "key:" << key << endl;
            break;
        }
    }

    // ͳ���ظ������Լ�����ֵĴ���
    unordered_map<int, int> m1;
    for (auto key : vec)
    {
        //auto it = m1.find(key);
        //if (it == m1.end())
        //{
        //    m1.emplace(key, 1);
        //}
        //else
        //{
        //    it->second++;
        //}

        m1[key]++;  // key������ʱ���Զ�����valueΪ0
    }

    for (auto pair : m1)
    {
        if (pair.second > 1)
        {
            cout << "key:" << pair.first << " cnt:" << pair.second << endl;
        }
    }

    // һ��������Щ�������ظ��ģ����ظ������ֹ��˵���ÿ������ֻ����һ��
    unordered_set<int> s2;
    for (auto key : vec)
    {
        s2.emplace(key);
    }

    return 0;
}
#endif