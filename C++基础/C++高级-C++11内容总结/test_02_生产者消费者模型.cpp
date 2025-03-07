#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

/*
* C++多线程编程 - 线程间的同步通信机制
* 
* 多线程编程两个问题：
* 1.线程间的互斥
* 存在竞态条件，即多线程程序执行的结果是一致的，不会随着CPU对线程不同的调用顺序，而产生不同的运行结果；
* 所以在临界区代码段需要保证原子操作，可以通过互斥锁mutex或者轻量级的无锁实现CAS；
* 
* 2.线程间的同步通信
* 生产者-消费者线程模型
* 
* unique_lock，lock_guard，condition_variable
* 1.lock_guard：不能用在函数参数传递或者返回过程中，只能用在简单的临界区代码段的互斥操作中；
* 2.unique_lock：可以使用在简单的临界区代码段的互斥操作中，也可以用在函数调用过程中；
* 3.condition_variable：wait和notify_one/all方法；
*/

#if 0
std::mutex mtx;  // 定义互斥锁，做线程间的互斥操作
std::condition_variable cv;  // 定义条件变量，做线程间的同步通信操作，需要和互斥锁mutex搭配使用

// C++ STL的所有容器都不是线程安全的
class Queue
{
public:
	void put(int val)
	{
		unique_lock<mutex> lck(mtx);
		while (!que.empty())
		{
			// que不为空，应该通知消费者去消费，消费完了再继续生产
			// 生产者线程应该 1.进入等待状态，2.并且把mtx互斥锁释放掉
			cv.wait(lck);
		}
		que.push(val);
		/*
		* notify_one：通知另外的一个线程
		* notify_all：通知其它所有线程
		* 其它线程得到通知后，就会从等待状态 -》阻塞状态-》等待获取互斥锁-》执行
		*/
		cv.notify_all();  // 通知消费者线程可以消费了
		cout << "生产者 生产：" << val << "号物品" << endl;
	}

	int get()
	{
		unique_lock<mutex> lck(mtx);
		while (que.empty())
		{
			// 消费者线程发现que是空的，通知生产者线程生产物品
			// 消费者线程进入 1.等待状态 2.并把mtx互斥锁释放掉
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all();  // 通知生产者线程生产
		cout << "消费者 消费：" << val << "号物品" << endl;
		return val;
	}
private:
	queue<int> que;
};


// 生产者生产一个物品，通知消费者消费一个，消费完了，消费者再通知生产者继续生产
void producer(Queue* q)  // 生产者线程
{
	for (int i = 1; i <= 10; ++i)
	{
		q->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void consumer(Queue* q)  // 消费者线程
{
	for (int i = 1; i <= 10; ++i)
	{
		q->get();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	Queue que;  // 线程共享队列
	thread t1(producer, &que);
	thread t2(consumer, &que);

	t1.join();
	t2.join();

	return 0;
}
#endif