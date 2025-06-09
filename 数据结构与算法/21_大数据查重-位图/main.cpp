// 21_�����ݲ���-λͼ.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>
using namespace std;

/*
��1�ڸ����������ֵ������1�ڣ��ʶ�����ЩԪ���ظ��ˣ�˭�ǵ�һ���ظ��ģ�˭�ǵ�һ�����ظ���(1��λ�������ݵ�״̬��2��λ�������ݵ�״̬)��   �ڴ�����100M

1�� = 100M
100M * 4 = 400M * 2 = 800M

λͼ�㷨
int bitmap[100000000/32+1]   3.2M

ȱ��:   int 20��    unsigned int 40��
1 3 1000000000
int bitmap[1000000000/32+1]  30M

3*4 = 12 * 2 = 24byte

�Ƽ����������У����ݵĸ��� >= �����������ֵ����ֵ�൱
*/

int main()
{
	vector<int> vec{ 12,78,90,78,123,8,9,90 };

	// ����λͼ����
	int maxNum = vec[0];
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] > maxNum)
			maxNum = vec[i];
	}

	int* bitMap = new int[maxNum / 32 + 1]();  // int -> 4�ֽ� -> 32λ
	unique_ptr<int> ptr(bitMap);

	for (auto key : vec)
	{
		int index = key / 32;
		int offset = key % 32;

		// ȡkey��Ӧ��λ��ֵ
		if (0 == (bitMap[index] & (1 << offset)))
		{
			// ��ʾkeyû�г��ֹ�
			bitMap[index] |= (1 << offset);  // ��ֵ
		}
		else
		{
			cout << key << "�ǵ�һ���ظ����ֵ�����" << endl;
			break;
		}
	}

	return 0;
}