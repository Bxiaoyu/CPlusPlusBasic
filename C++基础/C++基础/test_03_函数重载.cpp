#include <iostream>
#include <typeinfo>

using namespace std;

/*
* �������أ�
* 1��C++Ϊʲô֧�ֺ������أ�C���Բ�֧�ֺ������أ�
* C++���������������ʱ���ɺ�����+�����б�������ɣ�
* C���������������ʱ�����ɺ�����������
* 
* 2������������Ҫע��Щʲô��
* 3��C++��C���Դ���֮������໥���ã�
* C++����C���룺�޷�ֱ�ӵ��ã���Ҫ��C����������������extern "C"����;
* C����C++���룺�޷�ֱ�ӵ��ã���Ҫ��C++���������extern "C"���棻
* 
* ʲô�Ǻ������أ�
* 1����һ�麯�������к�������ͬ�������б�ĸ����������Ͳ�ͬ����ô��һ�麯���ͳ����������أ�
* 2����һ�麯��Ҫ�Ƶ������أ�һ�����ȴ���ͬһ���������У�
* 3����const����volatile��ʱ������ôӰ���β����͵ģ�
* 4����һ�麯������������ͬ�������б�Ҳ��ͬ�������Ƿ���ֵ��ͬ�����ܽ����أ�
* 
* ����һ�£�ʲô�Ƕ�̬��
* ��̬������ʱ�ڣ��Ķ�̬���������أ�����ģ��
* ��̬������ʱ�ڣ��Ķ�̬���麯�����麯����
*/

#if 0
#ifdef __cplusplus  // �����C++����������__cplusplus�꣩��������C����ķ��ţ������C��������û��__cplusplus�꣩��ֱ������C�������
extern "C" {
#endif
	int sum(int a, int b)
	{
		return a + b;
	}
#ifdef __cplusplus
}
#endif // __cplusplus
#endif



#if 0
// C++����C����
extern "C"
{
	// �����������������ɰ�C++����������
	int sum(int a, int b);  // sum "UND"
}

// ����C����C++����C���������������ü���
extern "C"
{
	int sum(int a, int b)  // �������ɰ�C����������
	{
		return a + b;
	}
}

int main()
{
	cout << "ret:" << sum(10, 20) << endl;
	return 0;
}
#endif

#if 0
void func(int a) {}
void func(const int a) {}

int main()
{
	int a = 10;
	const int b = 10;
	cout << typeid(a).name() << endl;  // int
	cout << typeid(b).name() << endl;  // int
}
#endif

#if 0
bool compare(int a, int b)  // compare_int_int
{
	cout << "compare_int_int" << endl;
	return a > b;
}

bool compare(double a, double b)  // compare_double_double
{
	cout << "compare_double_double" << endl;
	return a > b;
}

bool compare(const char* a, const char* b)  // compare_char*_char*
{
	cout << "compare_char*_char*" << endl;
	return strcmp(a, b) > 0;
}

int main()
{
	bool compare(int a, int b);  // ����������ȫ�ֵ�compare���ֲ�compare����

	compare(10, 20);
	compare(10.0, 20.0);  // double -> int
	compare("aaa", "bbb");  // const char* -> int
}
#endif