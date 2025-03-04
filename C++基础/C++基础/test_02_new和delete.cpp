#include <iostream>
#include <typeinfo>

using namespace std;

/*
* new��delete
* - malloc��free������C�Ŀ⺯��;
* - new��delete�����������;
* 
* 
* 1��new��malloc��������ʲô��
* a.malloc���ֽڿ����ڴ棬new�����ڴ�ʱ��Ҫָ�����ͣ���new int[10]��������malloc�����ڴ淵�ص���void*��
*	��new�����ڴ淵����������ָ�루��int*����
* b.mallocֻ���𿪱��ڴ�ռ䣬new������malloc�Ĺ��ܣ������Խ������ݳ�ʼ������ new int(20), new int[20]()����
* c.malloc�����ڴ�ʧ�ܷ���nullptrָ�룬new�����ڴ�ʧ�����׳�bad_alloc���͵��쳣��
* 
* 2��delete��free��������ʲô��
* delete���ȵ�����������free������ delete (int*)p;free(p)��
* 
* new -> operator new
* delete -> operator delete
* 
* 3��new��delete�ܻ�����C++Ϊʲô���ֵ���Ԫ�غ�������ڴ������ͷ��أ�
* new-delete
* new[]-delete[]
* a.������ͨ�ı������������ͣ�new/delete[] new[]/delete���Ի��ã�����Ҳ���Ƽ�;
* b.�Զ���������ͣ�������������Ϊ�˵�����ȷ�������������������ڿ��ٶ��������ʱ���࿪��4�ֽڣ�32λ�£�����¼����ĸ�����
*	��������²��ܻ��ã�
* c.Ϊ�˱��밲ȫ�ͱ���淶�����Ƽ����ã�
*/

#if 0
void* operator new(size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
	{
		throw bad_alloc();
	}
	cout << "operator new addr:" << p << endl;
	return p;
}

void operator delete(void* ptr)
{
	cout << "operator delete addr:" << ptr << endl;
	free(ptr);
}

void* operator new[](size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
	{
		throw bad_alloc();
	}
	cout << "operator new[] addr:" << p << endl;
	return p;
}

void operator delete[](void* ptr)
{
	cout << "operator delete[] addr:" << ptr << endl;
	free(ptr);
}


class Test
{
public:
	Test(int data = 10)
	{
		cout << "Test()" << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int ma;
};


int main()
{
	Test* t = new Test();
	delete[] t;  // ����

	Test* t1 = new Test[5];
	delete[] t1;
#if 0
	try
	{
		int* p = new int;
		delete p;

		int* p1 = new int[10];
		delete[] p1;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
#endif

#if 0
	// new�ж�����
	int* p1 = new int(20);
	int* p2 = new (nothrow) int;
	const int* p3 = new const int(40);
	// ��λnew
	int data = 0;
	int* p4 = new (&data)int(50);
	cout << "data:" << data << endl;
#endif

#if 0
	int* p = (int*)malloc(sizeof(int));
	if (p == nullptr)
	{
		return -1;
	}
	*p = 20;
	free(p);

	int* p1 = new int(20);
	delete p1;

	// ����
	int* q = (int*)malloc(sizeof(int) * 20);
	if (q == nullptr)
	{
		return -1;
	}
	free(q);

	//int* q1 = new int[20];  // ֻ�����ڴ�
	int* q1 = new int[20]();  // 20��int��sizeof(int)*20;�����ڴ沢��ʼ��
	delete[] q1;
#endif

	return 0;
}
#endif