#include <iostream>

using namespace std;

/*
* C++����ģ��:
* ģ�����壺������Ҳ���Խ��в�������
* 
* ����ģ�壺
* - �����б��룬��Ϊ���ͻ���֪����
* ģ���ʵ������
* - �������õ����ʵ������
* ģ�庯����
* - ����Ҫ��������������ģ���bool compare<int>(int a, int b)��
* 
* ģ�����Ͳ��� - typename/class
* ģ������Ͳ�����
* - ָ��ĳһ���������ͣ���template<typename T, int SIZE>
* - �������������ͣ��������ߵ�ַ/���ö����ԣ����Ҷ��ǳ�����ֻ��ʹ�ã������޸ģ�
* 
* ģ���ʵ�����ݣ�
* - ���Ը����û������ʵ�����ͣ����Ƶ���ģ�����Ͳ����ľ�������
* 
* ģ�����������ר�û�����
* - ����ĳЩ������˵������������Ĭ��ʵ������ģ����룬���봦���߼����д����;
* - ������Ҫ�����ʵ���������Ǳ������ṩ�ģ������û��ṩ�ģ�;
* 
* ����ģ�塢ģ�������������ģ�庯�������ع�ϵ��
* 
* ע�⣺
* ģ����벻����һ���ļ��ж��壬����һ���ļ���ʹ�ã�ģ��������֮ǰ��һ��Ҫ����ģ�嶨��ĵط���
* �����Ļ���ģ����ܽ���������ʵ�����������ܹ�������������Ĵ��룻����ģ����붨�嶼�Ƿ���ͷ��
* �����У�Ȼ����Դ�ļ���ֱ��#include����
*/
#if 0
// ����ģ�塢ģ�������������ģ�庯�������ع�ϵ��������ʾ��
// ����ģ��
template<typename T>
bool compare(T a, T b)
{
	cout << "template compare" << endl;
	return a > b;
}

// ���compare����ģ�壬�ṩconst char*���͵��������汾
template<>
bool compare<const char*>(const char* a, const char* b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

// ��ģ�庯�� - ��ͨ����
bool compare(const char* a, const char* b)
{
	cout << "normal compare" << endl;
	return strcmp(a, b) > 0;
}

/*
* �ں������õ㣬�����������û�ָ�������ͣ���ԭģ��ʵ����һ�ݺ����������
* ģ�庯��
* bool compare<int>(int a, int b)
* {
*		return a > b;
* }
* 
* bool compare<double>(double a, double b)
* {
*		return a > b;
* }
* 
* bool compare<const char*>(const char* a, const char* b)
* {
*		// ����ʹ�ñ�����Ĭ���ṩ�� a > b;
*		return strcmp(a, b) > 0;
* }
*/


// ģ������Ͳ�����ʾ��
// ʵ��һ��ð������
template<typename T, int SIZE>
void sort(T* arr)
{
	for (int i = 0; i < SIZE - 1; ++i)
	{
		for (int j = 0; j < SIZE - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				T tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

int main()
{
	// �������õ�
	compare<int>(10, 20);
	compare<double>(10, 20);

	// ����ģ��ʵ������
	compare(10, 20);
	//compare(10, 15.0);  // ����
	compare<int>(10, 15.0);  // ���漰������ת��

	// ����ģ��ʵ������ T -> const char*
	// ����ĳЩ������˵������������Ĭ��ʵ������ģ����룬���봦���߼����д����
	// ���������Ȱ�compare����ɺ������֣�û�еĻ���ȥ��compareģ��
	compare("aaa", "bbb");  // ���÷�ģ�庯��
	compare<const char*>("aaa", "bbb");  // ����ģ�庯��

	// ģ������Ͳ�����ʾ
	int arr[] = { 12,5,7,89,20,31 };
	const int size = sizeof(arr) / sizeof(arr[0]);
	sort<int, size>(arr);
	for (int val : arr)
	{
		cout << val << " ";
	}
	cout << endl;

	return 0;
}
#endif