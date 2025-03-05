#include <iostream>

using namespace std;

/*
* �����Ż�����
* 1�������������ݹ����У��������Ȱ����ô��ݣ���Ҫ��ֵ���ݣ����Լ���ʵ�ε��βεĿ�������ͺ������������������
* 2���������ض����ʱ��Ӧ�����ȷ���һ����ʱ���󣬶���Ҫ����һ��������Ķ���
* 3�����շ���ֵ�Ƕ���ĺ������õ�ʱ�����Ȱ���ʼ���ķ�ʽ���գ���Ҫ����ֵ�ķ�ʽ���գ�
*/
#if 0
class Test
{
public:
	Test(int data = 10) : ma(data)
	{
		cout << "Test(int)" << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}

	Test(const Test& t) :ma(t.ma)
	{
		cout << "Test(const Test& t)" << endl;
	}

	Test& operator=(const Test& t)
	{
		cout << "operator=" << endl;
		ma = t.ma;
		return *this;
	}

	int getData() const { return ma; }
private:
	int ma;
};

#if 0
Test getObject(Test t)  // ���ܷ��ؾֲ��Ļ�����ʱ�����ָ�������
{
	int val = t.getData();
	Test tmp(val);  // 4.Test(int)
	return tmp;  // 5.Test(const Test&)  ����һ��main����ջ֡�ϵ���ʱ���󲢷���
	// 6.tmp -> ~Test()
	// 7.t -> ~Test()
}

int main()
{
	Test t1;  // 1.Test(int)
	Test t2;  // 2.Test(int)
	/*
	* 3.getObject(t1) -> Test(const Test&)�βε�ʵ�εĳ�ʼ��
	* 8.operator=
	* 9.���ص���ʱ���� -> ~Test()
	*/
	t2 = getObject(t1);
	// 10.t2 -> ~Test()
	// 11.t1 -> ~Test()

	return 0;
}
#endif	

// �Ż������������ô��ݣ�������ʱ����
Test getObject(const Test& t)
{
	int val = t.getData();
	// ������ʱ����
	// 2.Test(int) ֱ�ӹ���
	return Test(val);  // ֱ����main����ջ֡�Ϲ���һ����ʱ���󣬼��ȹ�����ʱ�����ٿ������쵽main����ջ֡��ʱ����Ĺ���
}

int main()
{
	Test t1;  // 1.Test(int)
	Test t2 = getObject(t1);  // ��ʱ���󿽱�����ͬ���͵��¶���t2����ʱ���󲻲�����Ҳ��������
	// 3. t2 -> ~Test()
	// 4. t1 -> ~Test()
	return 0;
}
#endif