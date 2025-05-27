#include <iostream>
#include "threadpool.h"

using uLong = unsigned long	long;

class MyTask : public Task
{
public:
	MyTask(int begin, int end)
		: begin_(begin)
		, end_(end)
	{
	}

	// ����һ��������run�����ķ���ֵ�����Ա�ʾ���������
	Any run() override
	{
		std::cout << "tid:" << std::this_thread::get_id() << " begin." <<  std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		uLong sum = 0;
		for (uLong i = begin_; i <= end_; i++)
			sum += i;
		std::cout << "tid:" << std::this_thread::get_id() << " end." << std::endl;
		return sum;
	}

private:
	int begin_;
	int end_;
};

int main()
{
	{
		ThreadPool pool;
		pool.setMode(PoolMode::MODE_CACHED);
		pool.start(4);

		auto res = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
		auto res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		uLong sum1 = res.get().cast_<uLong>();
		std::cout << sum1 << std::endl;
		std::cout << "main over!" << std::endl;
	}

#if 0
	{
		ThreadPool pool;
		pool.setMode(PoolMode::MODE_CACHED);
		pool.start(4);

		auto res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
		auto res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		auto res3 = pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
		pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
		pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));
		pool.submitTask(std::make_shared<MyTask>(200000001, 300000000));

		uLong sum1 = res1.get().cast_<uLong>();
		uLong sum2 = res2.get().cast_<uLong>();
		uLong sum3 = res3.get().cast_<uLong>();

		std::cout << (sum1 + sum2 + sum3) << std::endl;
	}
	 
	//// �����������Result
	//Result res = pool.submitTask();
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
	//pool.submitTask(std::make_shared<MyTask>());
#endif
	std::getchar();
	return 0;
}