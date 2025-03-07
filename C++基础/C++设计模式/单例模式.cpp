#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/*
* 单例模式：一个类不管创建多少次对象，永远只能得到该类型的一个对象实例
* A* p1 = new A();
* A* p2 = new A();
* A* p3 = new A();
* 
* 常用到的：比如日志模块，数据库模块
* 
* 单例模式类型：
* 1.饿汉式单例模式：还没有获取实例对象，对象就已经产生了，一定是线程安全的；
* 2.懒汉式单例模式：唯一的实例对象，直到第一次获取它的时候才产生，线程不安全；
* 
* 饿汉单例有时候没必要，如果没用到此模块，也会占用一定资源，所以懒汉模式用的更多。
*/

// 饿汉式单例模式，一定是线程安全的
class SingletonE
{
public:
	// 3、获取类的唯一实例对象的接口方法
	static SingletonE* getInstance()
	{
		return &instance;
	}

	SingletonE(const SingletonE&) = delete;
	SingletonE& operator=(const SingletonE&) = delete;
private:
	static SingletonE instance;  // 2、定义一个唯一的类的实例对象
	SingletonE() {}  // 1、构造函数私有化
};

SingletonE SingletonE::instance;


std::mutex mtx;
// 懒汉式单例模式实现方式一，线程安全实现
// 锁 + 双重判断
class SingletonL
{
public:
	// 3、获取类的唯一实例对象的接口方法
	// 是不是可重入函数？即函数还没执行完，能否再次被调用（多线程环境下），并且不会发生竞态条件
	static SingletonL* getInstance()
	{
		if (instance == nullptr)
		{
			/*
			* 对象构造过程：
			* 开辟内存
			* 构造函数
			* 给instance赋值
			* 注意：由于编译器会对源代码进行顺序倒换（优化），所有会有可能造成构造对象和赋值的指令执行顺序不一致，也会造成问题，
			*      比如先赋值，但对象还没构造。
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
	// volatile关键字，线程不对共享变量进行缓存，直接使用变量原内存，内存变动可以被线程实时察觉
	static SingletonL* volatile instance;  // 2、定义一个唯一的类的实例对象
	SingletonL() {}  // 1、构造函数私有化
};

SingletonL* volatile SingletonL::instance = nullptr;


// 懒汉式单例模式实现方式二，线程安全实现，很精简
class SingletonL2
{
public:
	static SingletonL2* getInstance()
	{
		// 函数静态局部变量的初始化，在汇编指令上已经自动添加了线程互斥指令
		static SingletonL2 instance;  // 定义一个唯一的类的实例对象
		return &instance;
	}

	SingletonL2(const SingletonL2&) = delete;
	SingletonL2& operator=(const SingletonL2&) = delete;
private:
	SingletonL2() {}  // 构造函数私有化
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