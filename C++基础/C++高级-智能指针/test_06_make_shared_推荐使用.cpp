#include <iostream>
#include <memory>

using namespace std;

/*
* �Ƽ�ʹ��
* unique_ptr -> make_unique
* shared_ptr -> make_shared
* 
* make_shared��
* ���ַ�ʽ��������ָ�룬�����Ҫ�йܵ��ڴ���Դ�ʹ洢���ü������ڴ���Դ������ͬһ���ڴ��ϣ�
* 
* �ŵ㣺
* 1���ڴ����Ч�ʸߣ�ͬһ���ڴ���Դ��
* 2����ֹ��Դй¶�ķ��գ�
* 
* ȱ�㣺
* 1��make_shared�޷��Զ���ɾ������������Щ�ǹر��ļ���Դ������ɾ������
* 2�������йܵ���Դ�ӳ��ͷţ����������weak_ptr���ڹ۲죨����������������ʹ���ü����Ѿ�Ϊ0�ˣ��ǻ����������ͷ���Դ��
*/

#if 0
class Test
{
public:
	Test(int a) { cout << "Test(int)" << endl; }
	Test(int a, int b) { cout << "Test(int, int)" << endl; }
};

int main()
{
	// ���ַ�ʽ��������ָ�������⣬��ֱ𴴽�����Դ�����ü������������ڴ棬�����������ʧ�ܣ����ڴ�й¶���գ�
	shared_ptr<int> sp1(new int(10));
	shared_ptr<Test> sp2(new Test(10));

	// make_shared��ʽ�����������Ҫ�йܵ��ڴ���Դ�ʹ洢���ü������ڴ���Դ������ͬһ���ڴ��ϣ�
	shared_ptr<int> sp3 = make_shared<int>(10);
	auto sp4 = make_shared<Test>(10);  // new Test(10)
	auto sp5 = make_shared<Test>(10, 20);  // new Test(10,20)
	*sp3 = 20;
	cout << *sp3 << endl;
}
#endif