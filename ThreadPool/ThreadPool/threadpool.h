#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>

// 线程池支持的两种模式
enum class PoolMode
{
	MODE_FIXED,   // 固定数量模式
	MODE_CACHED,  // 可变数量模式
};

// Any类型，可以接收任意数据的类型
class Any
{
public:
	Any() = default;
	~Any() = default;

	Any(const Any&) = delete;
	Any& operator=(const Any&) = delete;

	Any(Any&&) = default;
	Any& operator=(Any&&) = default;

	template<typename T>
	Any(T data) : base_(std::make_unique<Derive<T>>(data))
	{
	}

	// 此方法把Any对象里存储的data数据提取出来
	template<typename T>
	T cast_()
	{
		// 基类指针 -》派生类指针 RTTI
		Derive<T>* pd = dynamic_cast<Derive<T>*>(base_.get());
		if (pd == nullptr)
		{
			throw "type is unmatch!";
		}

		return pd->data_;
	}

private:
	// 基类类型
	class Base
	{
	public:
		virtual ~Base() = default;
	};

	// 派生类类型
	template<typename T>
	class Derive : public Base
	{
	public:
		Derive(T data) : data_(data) {}
	public:
		T data_;
	};

private:
	// 定义一个基类指针
	std::unique_ptr<Base> base_;
};


// 实现一个信号量
class Semaphore
{
public:
	Semaphore(int limit = 0) : resLimit_(limit)
	{
	}

	~Semaphore() = default;

	// 获取一个信号量资源
	void wait()
	{
		std::unique_lock<std::mutex> lock(mtx_);
		// 等待信号量有资源，没有资源的话会阻塞当前线程
		cond_.wait(lock, [&]()->bool {return resLimit_ > 0;});
		resLimit_--;
	}

	// 增加一个信号量资源
	void post()
	{
		std::unique_lock<std::mutex> lock(mtx_);
		resLimit_++;
		cond_.notify_all();
	}

private:
	int resLimit_;
	std::mutex mtx_;
	std::condition_variable cond_;
};

class Task;
// 实现接收提交到线程池的task任务执行完毕后的返回值类型Result
class Result
{
public:
	Result(std::shared_ptr<Task> task, bool isValid = true);
	~Result() = default;

	// 问题一：setVal方法，获取任务执行完的返回值
	void setVal(Any any);

	// 问题二：get方法，用户调用这个方法获取task返回值
	Any get();

private:
	Any any_;                      // 存储任务返回值
	Semaphore sem_;                // 线程通信信号量
	std::shared_ptr<Task> task_;   // 指向对应获取返回值的任务对象
	std::atomic_bool isValid_;     // 返回值是否有效
};

// 任务抽象基类
class Task
{
public:
	Task();

	~Task() = default;

	void exec();

	void setResult(Result* res);

	// 用户可以自定义任意任务类型，从Task继承，重写run方法
	virtual Any run() = 0;

private:
	Result* result_;  // 这里使用普通指针，避免使用智能指针造成和Result的强智能指针交叉引用
};

// 线程类
class Thread
{
public:
	// 线程函数对象类型
	using ThreadFunc = std::function<void(int)>;

	// 线程构造
	Thread(ThreadFunc func);

	// 线程析构
	~Thread();

	// 启动线程
	void start();

	// 获取线程ID
	int getId() const;
private:
	ThreadFunc func_;
	static int generateId_;  // 生成局部线程ID
	int threadId_;  // 保存线程ID
};


/*
* example:
* ThreadPool pool;
* pool.start(4);
* 
* class MyTask : public Task
* {
*	public:
*		void run(){// 线程代码 ...}
* };
* 
* pool.submitTask(std::make_shared<MyTask>());
*/
// 线程池类
class ThreadPool
{
public:
	// 线程池构造
	ThreadPool();

	// 线程池析构
	~ThreadPool();

	// 禁止拷贝构造和赋值
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

	// 设置线程池的工作模式
	void setMode(PoolMode mode);

	// 设置线程池cached模式下线程阈值
	void setThreadSizeThreshHold(int threshhold);

	// 设置task任务队列上限阈值
	void setTaskQueMaxThreshHold(int threshhold);

	// 给线程池提交任务
	Result submitTask(std::shared_ptr<Task> sp);

	// 开启线程池
	void start(int initThreadSize = std::thread::hardware_concurrency());

private:
	// 定义线程函数
	void threadFunc(int threadId);

	// 检查线程池运行状态
	bool checkRunningState() const;

private:
	//std::vector<std::unique_ptr<Thread>> threads_;  // 线程列表
	std::unordered_map<int, std::unique_ptr<Thread>> threads_;  // 线程列表
	int initThreadSize_;                            // 初始线程数量
	int threadSizeThreshHold_;                      // 线程数量上限阈值
	std::atomic_int curThreadSize_;                 // 记录当前线程池里线程总数量
	std::atomic_int idleThreadSize_;                // 记录空闲线程数量

	std::queue<std::shared_ptr<Task>> taskQue_;  // 任务队列
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
