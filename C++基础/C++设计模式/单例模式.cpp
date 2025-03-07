#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/*
* ����ģʽ��һ���಻�ܴ������ٴζ�����Զֻ�ܵõ������͵�һ������ʵ��
* A* p1 = new A();
* A* p2 = new A();
* A* p3 = new A();
* 
* ���õ��ģ�������־ģ�飬���ݿ�ģ��
* 
* ����ģʽ���ͣ�
* 1.����ʽ����ģʽ����û�л�ȡʵ�����󣬶�����Ѿ������ˣ�һ�����̰߳�ȫ�ģ�
* 2.����ʽ����ģʽ��Ψһ��ʵ������ֱ����һ�λ�ȡ����ʱ��Ų������̲߳���ȫ��
* 
* ����������ʱ��û��Ҫ�����û�õ���ģ�飬Ҳ��ռ��һ����Դ����������ģʽ�õĸ��ࡣ
*/

// ����ʽ����ģʽ��һ�����̰߳�ȫ��
class SingletonE
{
public:
	// 3����ȡ���Ψһʵ������Ľӿڷ���
	static SingletonE* getInstance()
	{
		return &instance;
	}

	SingletonE(const SingletonE&) = delete;
	SingletonE& operator=(const SingletonE&) = delete;
private:
	static SingletonE instance;  // 2������һ��Ψһ�����ʵ������
	SingletonE() {}  // 1�����캯��˽�л�
};

SingletonE SingletonE::instance;


std::mutex mtx;
// ����ʽ����ģʽʵ�ַ�ʽһ���̰߳�ȫʵ��
// �� + ˫���ж�
class SingletonL
{
public:
	// 3����ȡ���Ψһʵ������Ľӿڷ���
	// �ǲ��ǿ����뺯������������ûִ���꣬�ܷ��ٴα����ã����̻߳����£������Ҳ��ᷢ����̬����
	static SingletonL* getInstance()
	{
		if (instance == nullptr)
		{
			/*
			* ��������̣�
			* �����ڴ�
			* ���캯��
			* ��instance��ֵ
			* ע�⣺���ڱ��������Դ�������˳�򵹻����Ż��������л��п�����ɹ������͸�ֵ��ָ��ִ��˳��һ�£�Ҳ��������⣬
			*      �����ȸ�ֵ��������û���졣
			*/
			std::lock_guard<std::mutex> lock(mtx);
			if (instance == nullptr)
			{
				instance = new SingletonL();
			}
		}

		return instance;
	}

	SingletonL(const SingletonL&) = delete;
	SingletonL& operator=(const SingletonL&) = delete;
private:
	// volatile�ؼ��֣��̲߳��Թ���������л��棬ֱ��ʹ�ñ���ԭ�ڴ棬�ڴ�䶯���Ա��߳�ʵʱ���
	static SingletonL* volatile instance;  // 2������һ��Ψһ�����ʵ������
	SingletonL() {}  // 1�����캯��˽�л�
};

SingletonL* volatile SingletonL::instance = nullptr;


// ����ʽ����ģʽʵ�ַ�ʽ�����̰߳�ȫʵ�֣��ܾ���
class SingletonL2
{
public:
	static SingletonL2* getInstance()
	{
		// ������̬�ֲ������ĳ�ʼ�����ڻ��ָ�����Ѿ��Զ�������̻߳���ָ��
		static SingletonL2 instance;  // ����һ��Ψһ�����ʵ������
		return &instance;
	}

	SingletonL2(const SingletonL2&) = delete;
	SingletonL2& operator=(const SingletonL2&) = delete;
private:
	SingletonL2() {}  // ���캯��˽�л�
};

#if 0
int main()
{
	SingletonE* p1 = SingletonE::getInstance();
	SingletonE* p2 = SingletonE::getInstance();
	SingletonE* p3 = SingletonE::getInstance();

	SingletonL* p4 = SingletonL::getInstance();
	SingletonL* p5 = SingletonL::getInstance();
	SingletonL* p6 = SingletonL::getInstance();

	SingletonL2* p7 = SingletonL2::getInstance();
	SingletonL2* p8 = SingletonL2::getInstance();
	SingletonL2* p9 = SingletonL2::getInstance();

	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << "-----------------------" << endl;
	cout << p4 << endl;
	cout << p5 << endl;
	cout << p6 << endl;
	cout << "-----------------------" << endl;
	cout << p7 << endl;
	cout << p8 << endl;
	cout << p9 << endl;

	return 0;
}
#endif