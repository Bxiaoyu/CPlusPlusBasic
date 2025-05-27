#include "threadpool.h"
#include <chrono>


/*
* ��������̳߳��ύ���������
* 
* 1. pool.submitTask(sum1, 10, 20);
*    pool.submitTask(sum2, 1, 2, 3);
*    submitTask���ɱ��ģ����
* 
* 2. �����Լ�����һ��Result�Լ�������ͣ�����ͦ��
*    C++11 �߳̿� thread packaged_task(function��������) async
*    ʹ��future������Result��ʡ�̳߳ش���
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