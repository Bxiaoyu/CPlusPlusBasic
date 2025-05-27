#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>
#include <future>

const int TASK_MAX_THRESHHOLD = INT32_MAX;
const int THREAD_MAX_THRESHHOLD = 100;
const int THREAD_MAX_IDLE_TIME = 60;  // 单位:秒

// 线程池支持的两种模式
enum class PoolMode
{
	MODE_FIXED,   // 固定数量模式
	MODE_CACHED,  // 可变数量模式
};

// 线程类
class Thread
{
public:
	// 线程函数对象类型
	using ThreadFunc = std::function<void(int)>;

	// 线程构造
	Thread(ThreadFunc func)
		: func_(func)
		, threadId_(generateId_++)
	{
	}

	// 线程析构
	~Thread() = default;

	// 启动线程
	void start()
	{
		// 创建一个线程并执行线程函数
		std::thread t(func_, threadId_);
		t.detach();  // 设置分离线程，线程对象出作用域析构以后不影响线程函数执行
	}

	// 获取线程ID
	int getId() const
	{
		return threadId_;
	}
private:
	ThreadFunc func_;
	static int generateId_;  // 生成局部线程ID
	int threadId_;  // 保存线程ID
};

int Thread::generateId_ = 0;

// 线程池类
class ThreadPool
{
public:
	// 线程池构造
	ThreadPool()
		: initThreadSize_(0)
		, idleThreadSize_(0)
		, threadSizeThreshHold_(THREAD_MAX_THRESHHOLD)
		, curThreadSize_(0)
		, taskSize_(0)
		, taskQueMaxThreshHold_(TASK_MAX_THRESHHOLD)
		, poolMode_(PoolMode::MODE_FIXED)
		, isPoolRunning_(false)
	{

	}

	// 线程池析构
	~ThreadPool()
	{
		isPoolRunning_ = false;

		// 等待线程池里面所有线程返回，有两种状态：阻塞 & 正在执行任务
		std::unique_lock<std::mutex> lock(taskQueMtx_);
		notEmpty_.notify_all();
		exitCond_.wait(lock, [&]()->bool {return threads_.size() == 0;});
	}

	// 禁止拷贝构造和赋值
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

	// 设置线程池的工作模式
	void setMode(PoolMode mode)
	{
		if (checkRunningState()) return;
		poolMode_ = mode;
	}

	// 设置线程池cached模式下线程阈值
	void setThreadSizeThreshHold(int threshhold)
	{
		if (checkRunningState()) return;
		if (poolMode_ != PoolMode::MODE_CACHED) return;
		threadSizeThreshHold_ = threshhold;
	}

	// 设置task任务队列上限阈值
	void setTaskQueMaxThreshHold(int threshhold)
	{
		if (checkRunningState()) return;
		taskQueMaxThreshHold_ = threshhold;
	}

	// 给线程池提交任务
	// 使用可变参模板编程，让submitTask可以接收任意任务函数和任意数量的参数
	// 右值引用+引用折叠
	// decltype：根据表达式推导返回值
	// 返回值future<类型>
	template<typename Func, typename... Args>
	auto submitTask(Func&& func, Args&&... args) -> std::future<decltype(func(args...))>
	{
		// 打包任务，放入任务队列
		using RType = decltype(func(args...));
		auto task = std::make_shared<std::packaged_task<RType()>>(
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
		);
		std::future<RType> result = task->get_future();

		// 获取锁
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		// 线程的通信，等待任务队列有空余
		// 用户提交任务最长不能阻塞超过1s，否则判断提交任务失败，返回
		if (!notFull_.wait_for(lock, std::chrono::seconds(1),
			[&]()->bool {return taskQue_.size() < (size_t)taskQueMaxThreshHold_;}))
		{
			// 表示notFull_等待1s，条件依然没有满足，超时返回
			std::cerr << "task queue is full, submit task failed." << std::endl;
			auto task = std::make_shared<std::packaged_task<RType()>>(
				[]()->RType {return RType();}
			);
			(*task)();
			return task->get_future();
		}

		// 如果有空余，把任务放入任务队列
		// using Task = std::function<void()>
		taskQue_.emplace([task]() {(*task)();});
		taskSize_++;

		// notEmpty_通知，分配线程执行任务
		notEmpty_.notify_all();

		// cached模式 任务处理比较紧急 场景：小而快的任务 需要根据任务数量和空闲线程数量，判断是否需要创建新线程
		if (poolMode_ == PoolMode::MODE_CACHED && taskSize_ > idleThreadSize_ && curThreadSize_ < threadSizeThreshHold_)
		{
			// 创建新线程
			std::cout << ">> create new thread <<<" << std::endl;
			auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));
			threads_[threadId]->start();  // 启动线程
			curThreadSize_++;
			idleThreadSize_++;
		}

		// 返回任务的Result对象
		return result;
	}

	// 开启线程池
	void start(int initThreadSize = std::thread::hardware_concurrency())
	{
		// 设置线程池运行状态
		isPoolRunning_ = true;

		// 记录初始线程个数
		this->initThreadSize_ = initThreadSize;
		this->curThreadSize_ = initThreadSize;

		// 创建线程对象
		for (int i = 0; i < initThreadSize_; i++)
		{
			// 创建thread线程对象的时候，把线程函数给到thread线程对象
			auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));  // 函数绑定器
			// threads_.emplace_back(std::move(ptr));  // unique_ptr只支持右值拷贝和赋值，禁止左值拷贝和赋值, unique_ptr(const unique_ptr&) = delete;unique_ptr& operator=(const unique_ptr&) = delete;
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));
		}

		// 启动线程对象
		for (int i = 0; i < initThreadSize_; i++)
		{
			threads_[i]->start();
			idleThreadSize_++;     // 记录初始空闲线程数量
		}
	}

private:
	// 定义线程函数
	void threadFunc(int threadId)
	{
		auto lastTime = std::chrono::high_resolution_clock().now();

		// 所有任务必须执行完，线程池才可以回收所有线程资源
		for (;;)
		{
			Task task;
			{
				// 先获取锁
				std::unique_lock<std::mutex> lock(taskQueMtx_);

				std::cout << "tid:" << std::this_thread::get_id() << " 尝试获取任务..." << std::endl;

				// cached模式下，有可能已经创建了很多线程，但是空闲时间超过60s，应该把多余线程结束回收（超过initThreadSize_的线程要回收）
				// (当前时间 - 上一次线程执行时间) > 60s
				// 每一秒返回一次 怎么区分：超时返回？还是有任务待执行返回
				// 锁+ 双重判断
				while (taskQue_.size() == 0)
				{
					// 线程池要结束，回收线程资源
					if (!isPoolRunning_)
					{
						threads_.erase(threadId);
						exitCond_.notify_all();
						std::cout << "threadid: " << std::this_thread::get_id() << " exit!" << std::endl;
						return;  // 线程函数结束，线程结束
					}

					if (poolMode_ == PoolMode::MODE_CACHED)
					{
						// 条件变量，超时返回
						if (std::cv_status::timeout == notEmpty_.wait_for(lock, std::chrono::seconds(1)))
						{
							auto now = std::chrono::high_resolution_clock().now();
							auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);
							if (dur.count() >= THREAD_MAX_IDLE_TIME && curThreadSize_ > initThreadSize_)
							{
								// 开始回收当前线程
								// 记录线程数量的相关变量的值修改
								// 把线程对象从线程列表容器中删除
								threads_.erase(threadId);
								curThreadSize_--;
								idleThreadSize_--;
								std::cout << "threadid: " << std::this_thread::get_id() << " exit." << std::endl;
								return;
							}
						}
					}
					else
					{
						// 等待notEmpty_条件
						notEmpty_.wait(lock);
					}
				}

				idleThreadSize_--;

				std::cout << "tid:" << std::this_thread::get_id() << " 获取任务成功..." << std::endl;

				// 从任务队列取出一个任务
				task = taskQue_.front();
				taskQue_.pop();
				taskSize_--;

				// 如果依然有剩余任务，继续通知其它线程执行任务
				if (taskQue_.size() > 0) notEmpty_.notify_all();

				// 取出任务后，进行通知
				notFull_.notify_all();

			}  // 执行任务前，将锁释放掉，避免影响其它线程正常获取锁

			// 当前线程负责执行这个任务
			if (task != nullptr)
			{
				task();  // 调用此处自动完成返回值赋值
			}

			idleThreadSize_++;
			lastTime = std::chrono::high_resolution_clock().now();  // 更新线程执行完任务的时间
		}
	}

	// 检查线程池运行状态
	bool checkRunningState() const
	{
		return isPoolRunning_;
	}

private:
	//std::vector<std::unique_ptr<Thread>> threads_;  // 线程列表
	std::unordered_map<int, std::unique_ptr<Thread>> threads_;  // 线程列表
	int initThreadSize_;                            // 初始线程数量
	int threadSizeThreshHold_;                      // 线程数量上限阈值
	std::atomic_int curThreadSize_;                 // 记录当前线程池里线程总数量
	std::atomic_int idleThreadSize_;                // 记录空闲线程数量

	// Task任务-》函数对象
	using Task = std::function<void()>;          // 这里不能确定返回值类型，所以用void，在实际代码中通过中间层封装达到相应目的
	std::queue<Task> taskQue_;                   // 任务队列
	std::atomic_int taskSize_;                   // 当前任务数量
	int taskQueMaxThreshHold_;                   // 任务数量上限阈值

	std::mutex taskQueMtx_;             // 保证任务队列线程安全
	std::condition_variable notFull_;   // 表示任务队列不满
	std::condition_variable notEmpty_;  // 表示任务队列不空
	std::condition_variable exitCond_;  // 等待线程资源全部回收

	PoolMode poolMode_;  // 当前线程池的工作模式

	std::atomic_bool isPoolRunning_;  // 表示当前线程池的启动状态
};

#endif // !THREADPOOL_H
