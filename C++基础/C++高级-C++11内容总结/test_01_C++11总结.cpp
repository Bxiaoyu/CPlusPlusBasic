#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>  // 包含很多原子类型
#include <list>

using namespace std;

/*
* C++11标准相关内容总结：
* 
* 一、关键字和语法：
* 1.auto：可以根据右值推导出右值的类型，然后左边变量的类型也就知道了；
* 2.nullptr：给指针专用（能够和整数进行区别）。老的NULL -》 #define NULL 0；
* 3.foreach：可以遍历数组，容器等；
*	for(Type val : container)  // 底层就是通过指针或者迭代器来实现
*	{
*		cout << val << " ";
*	}
* 
* 4.右值引用：move移动语义函数和forward类型完美转发函数，能对对象的优化起很大作用；
* 5.模板的一个新特性：typename... A  表示可变参（类型参数）；
* 
* 二、绑定器和函数对象：
* 1.function：函数对象；
* 2.bind：绑定器，对原来STL中bind1st和bind2nd的升级；
* 3.lambda表达式；
* 
* 三、智能指针：
* 1.shared_ptr和weak_ptr；
* 
* 四、新增容器：
* 原来只有set和map：通过红黑树实现，有序；
* 1.unordered_set和unordered_map：通过哈希表实现，无序 增删查O(1)；
* 2.array：数组（不支持动态扩容），原来只有vector；
* 3.forward_list：前向链表，原来只有list（双向循环链表）；
* 
* 五、C++语言级别支持的多线程编程（可以跨平台）：
* 1.thread：线程类；
* 2.mutex：互斥锁；
* 3.condition_variable：条件变量；
* 4.lock_guard和unique_lock：智能指针类型的加锁解锁；
* 5.atomic：原子类型，基于CAS操作的原子类型，线程安全；
* 6.sleep_for；
* 等。
* 
* C++语言层面 thread
* Windows              linux
*	 |                    |
* createThread       pthread_create
*/


/*
* 线程内容：
* 一、如何创建和启动一个线程？
* std::thread定义一个线程对象，传入线程所需的线程函数和参数，线程自动启动；
* 
* 二、子线程如何结束？
* 子线程函数运行完成，线程就结束；
* 
* 三、主线程如何处理子线程？
* 1、t.join()：等待t线程结束，当前线程继续往下运行；
* 2、t.detach()：t线程设置为分离线程，主线程结束，整个进程结束，所有子线程都自动结束了；
*/
#if 0
void threadHandle1(int time)
{
	// 让子线程睡眠两秒
	this_thread::sleep_for(std::chrono::seconds(time));
	cout << this_thread::get_id() << " hello thread!" << endl;
}

int main()
{
	// 创建一个线程对象，传入一个线程函数，新线程就开始运行了
	thread t1(threadHandle1, 2);
	thread t2(threadHandle1, 3);
	// 主线程等待子线程结束，主线程继续往下运行
	t1.join();
	t2.join();
	// 把子线程设置为分离线程
	//t1.detach();

	cout << "Main thread done." << endl;

	/*
	* 主线程运行完成，查看如果当前进程还有未运行完成的子线程，进程就会异常终止
	*/

	return 0;
}
#endif

/*
* 多线程程序：
* 竞态条件：多线程程序执行的结果是一致的，不会随着CPU对线程不同的调用顺序，而产生不同的运行结果；
* 
* 使用互斥锁解决竞态问题示例：
* 模拟车站三个窗口卖票程序
*/

#if 0
int ticketCount = 100; // 车站有100张车票，由三个窗口一起卖票
std::mutex mtx;  // 全局互斥锁

// 模拟卖票线程函数
void sellTicket(int index)
{
	while (ticketCount > 0)  // ticketCount = 1 锁+双重判断
	{
		{
			//std::unique_lock<std::mutex> lock(mtx);
			std::lock_guard<std::mutex> lock(mtx);
			if (ticketCount > 0)
			{
				// 临界区代码段，保持原子操作，线程间互斥
				cout << "窗口：" << index << "卖出第：" << ticketCount << "张票." << endl;
				ticketCount--;
			}
		}
		this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	list<thread> tlist;
	for (int i = 1; i <= 3; ++i)
	{
		tlist.push_back(thread(sellTicket, i));
	}

	for (thread& t : tlist)
	{
		t.join();
	}

	cout << "所有窗口卖票结束！" << endl;
	return 0;
}
#endif

/*
* 使用原子类型代替互斥锁解决简单竞态问题
* 原先用互斥锁实现：
* lock_guard<mutex> lock(mtx);
* count++;
* 
* lock_guard<mutex> lock(mtx);
* count--;
* 
* 互斥锁是比较重的，临界区代码做的事情稍稍复杂，多
* 系统理论：CAS保证上面++，--操作的原子特性就足够了，无锁操作
*          exchange/swap  无锁队列 -》CAS来实现的
*/
#if 0
// volatile关键字，防止共享变量被多线程缓存，保证线程访问的都是变量原始内存数据
// 虽然缓存有好处，但是有时候也会带来麻烦
volatile std::atomic_bool isReady = false;
volatile std::atomic_int _count = 0;

void task()
{
	while (!isReady)
	{
		std::this_thread::yield();  // 线程出让当前的CPU时间片，等待下一次调度
	}

	for (int i = 0; i < 100; ++i)
	{
		_count++;
	}
}

int main()
{
	list<thread> tlist;
	for (int i = 0; i < 10; ++i)
	{
		tlist.push_back(thread(task));
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));
	isReady = true;

	for (auto& t : tlist)
	{
		t.join();
	}

	cout << "count:" << _count << endl;

	return 0;
}
#endif