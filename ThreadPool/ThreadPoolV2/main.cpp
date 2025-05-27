#include "threadpool.h"
#include <chrono>


/*
* 如何能让线程池提交任务更方便
* 
* 1. pool.submitTask(sum1, 10, 20);
*    pool.submitTask(sum2, 1, 2, 3);
*    submitTask：可变参模板编程
* 
* 2. 我们自己造了一个Result以及相关类型，代码挺多
*    C++11 线程库 thread packaged_task(function函数对象) async
*    使用future来代替Result节省线程池代码
*/


int sum(int a, int b)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return a + b;
}

int sum2(int a, int b, int c)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return a + b + c;
}

class Task
{
public:
	Task();
	~Task() = default;

	int sum(int a, int b)
	{
		return a + b;
	}
};

int main()
{
	ThreadPool pool;
	pool.setMode(PoolMode::MODE_CACHED);
	pool.start(2);

	std::future<int> res1 = pool.submitTask(sum, 1, 2);
	std::future<int> res2 = pool.submitTask(sum2, 1, 2, 3);
	std::future<int> res3 = pool.submitTask(sum, 1, 2);
	std::future<int> res4 = pool.submitTask([](int b, int e)->int {
		int sum = 0;
		for (int i = b; i <= e; i++)
			sum += i;
		return sum;
		}, 1, 100);
	std::future<int> res5 = pool.submitTask([](int b, int e)->int {
		int sum = 0;
		for (int i = b; i <= e; i++)
			sum += i;
		return sum;
		}, 1, 100);
	std::future<int> res6 = pool.submitTask([](int b, int e)->int {
		int sum = 0;
		for (int i = b; i <= e; i++)
			sum += i;
		return sum;
		}, 1, 100);
	
	std::cout << res1.get() << std::endl;
	std::cout << res2.get() << std::endl;
	std::cout << res3.get() << std::endl;
	std::cout << res4.get() << std::endl;
	std::cout << res5.get() << std::endl;
	std::cout << res6.get() << std::endl;

	return 0;
}