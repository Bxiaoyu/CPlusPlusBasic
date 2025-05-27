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
const int THREAD_MAX_IDLE_TIME = 60;  // ��λ:��

// �̳߳�֧�ֵ�����ģʽ
enum class PoolMode
{
	MODE_FIXED,   // �̶�����ģʽ
	MODE_CACHED,  // �ɱ�����ģʽ
};

// �߳���
class Thread
{
public:
	// �̺߳�����������
	using ThreadFunc = std::function<void(int)>;

	// �̹߳���
	Thread(ThreadFunc func)
		: func_(func)
		, threadId_(generateId_++)
	{
	}

	// �߳�����
	~Thread() = default;

	// �����߳�
	void start()
	{
		// ����һ���̲߳�ִ���̺߳���
		std::thread t(func_, threadId_);
		t.detach();  // ���÷����̣߳��̶߳���������������Ժ�Ӱ���̺߳���ִ��
	}

	// ��ȡ�߳�ID
	int getId() const
	{
		return threadId_;
	}
private:
	ThreadFunc func_;
	static int generateId_;  // ���ɾֲ��߳�ID
	int threadId_;  // �����߳�ID
};

int Thread::generateId_ = 0;

// �̳߳���
class ThreadPool
{
public:
	// �̳߳ع���
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

	// �̳߳�����
	~ThreadPool()
	{
		isPoolRunning_ = false;

		// �ȴ��̳߳����������̷߳��أ�������״̬������ & ����ִ������
		std::unique_lock<std::mutex> lock(taskQueMtx_);
		notEmpty_.notify_all();
		exitCond_.wait(lock, [&]()->bool {return threads_.size() == 0;});
	}

	// ��ֹ��������͸�ֵ
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

	// �����̳߳صĹ���ģʽ
	void setMode(PoolMode mode)
	{
		if (checkRunningState()) return;
		poolMode_ = mode;
	}

	// �����̳߳�cachedģʽ���߳���ֵ
	void setThreadSizeThreshHold(int threshhold)
	{
		if (checkRunningState()) return;
		if (poolMode_ != PoolMode::MODE_CACHED) return;
		threadSizeThreshHold_ = threshhold;
	}

	// ����task�������������ֵ
	void setTaskQueMaxThreshHold(int threshhold)
	{
		if (checkRunningState()) return;
		taskQueMaxThreshHold_ = threshhold;
	}

	// ���̳߳��ύ����
	// ʹ�ÿɱ��ģ���̣���submitTask���Խ������������������������Ĳ���
	// ��ֵ����+�����۵�
	// decltype�����ݱ��ʽ�Ƶ�����ֵ
	// ����ֵfuture<����>
	template<typename Func, typename... Args>
	auto submitTask(Func&& func, Args&&... args) -> std::future<decltype(func(args...))>
	{
		// ������񣬷����������
		using RType = decltype(func(args...));
		auto task = std::make_shared<std::packaged_task<RType()>>(
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
		);
		std::future<RType> result = task->get_future();

		// ��ȡ��
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		// �̵߳�ͨ�ţ��ȴ���������п���
		// �û��ύ�����������������1s�������ж��ύ����ʧ�ܣ�����
		if (!notFull_.wait_for(lock, std::chrono::seconds(1),
			[&]()->bool {return taskQue_.size() < (size_t)taskQueMaxThreshHold_;}))
		{
			// ��ʾnotFull_�ȴ�1s��������Ȼû�����㣬��ʱ����
			std::cerr << "task queue is full, submit task failed." << std::endl;
			auto task = std::make_shared<std::packaged_task<RType()>>(
				[]()->RType {return RType();}
			);
			(*task)();
			return task->get_future();
		}

		// ����п��࣬����������������
		// using Task = std::function<void()>
		taskQue_.emplace([task]() {(*task)();});
		taskSize_++;

		// notEmpty_֪ͨ�������߳�ִ������
		notEmpty_.notify_all();

		// cachedģʽ ������ȽϽ��� ������С��������� ��Ҫ�������������Ϳ����߳��������ж��Ƿ���Ҫ�������߳�
		if (poolMode_ == PoolMode::MODE_CACHED && taskSize_ > idleThreadSize_ && curThreadSize_ < threadSizeThreshHold_)
		{
			// �������߳�
			std::cout << ">> create new thread <<<" << std::endl;
			auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));
			threads_[threadId]->start();  // �����߳�
			curThreadSize_++;
			idleThreadSize_++;
		}

		// ���������Result����
		return result;
	}

	// �����̳߳�
	void start(int initThreadSize = std::thread::hardware_concurrency())
	{
		// �����̳߳�����״̬
		isPoolRunning_ = true;

		// ��¼��ʼ�̸߳���
		this->initThreadSize_ = initThreadSize;
		this->curThreadSize_ = initThreadSize;

		// �����̶߳���
		for (int i = 0; i < initThreadSize_; i++)
		{
			// ����thread�̶߳����ʱ�򣬰��̺߳�������thread�̶߳���
			auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));  // ��������
			// threads_.emplace_back(std::move(ptr));  // unique_ptrֻ֧����ֵ�����͸�ֵ����ֹ��ֵ�����͸�ֵ, unique_ptr(const unique_ptr&) = delete;unique_ptr& operator=(const unique_ptr&) = delete;
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));
		}

		// �����̶߳���
		for (int i = 0; i < initThreadSize_; i++)
		{
			threads_[i]->start();
			idleThreadSize_++;     // ��¼��ʼ�����߳�����
		}
	}

private:
	// �����̺߳���
	void threadFunc(int threadId)
	{
		auto lastTime = std::chrono::high_resolution_clock().now();

		// �����������ִ���꣬�̳߳زſ��Ի��������߳���Դ
		for (;;)
		{
			Task task;
			{
				// �Ȼ�ȡ��
				std::unique_lock<std::mutex> lock(taskQueMtx_);

				std::cout << "tid:" << std::this_thread::get_id() << " ���Ի�ȡ����..." << std::endl;

				// cachedģʽ�£��п����Ѿ������˺ܶ��̣߳����ǿ���ʱ�䳬��60s��Ӧ�ðѶ����߳̽������գ�����initThreadSize_���߳�Ҫ���գ�
				// (��ǰʱ�� - ��һ���߳�ִ��ʱ��) > 60s
				// ÿһ�뷵��һ�� ��ô���֣���ʱ���أ������������ִ�з���
				// ��+ ˫���ж�
				while (taskQue_.size() == 0)
				{
					// �̳߳�Ҫ�����������߳���Դ
					if (!isPoolRunning_)
					{
						threads_.erase(threadId);
						exitCond_.notify_all();
						std::cout << "threadid: " << std::this_thread::get_id() << " exit!" << std::endl;
						return;  // �̺߳����������߳̽���
					}

					if (poolMode_ == PoolMode::MODE_CACHED)
					{
						// ������������ʱ����
						if (std::cv_status::timeout == notEmpty_.wait_for(lock, std::chrono::seconds(1)))
						{
							auto now = std::chrono::high_resolution_clock().now();
							auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);
							if (dur.count() >= THREAD_MAX_IDLE_TIME && curThreadSize_ > initThreadSize_)
							{
								// ��ʼ���յ�ǰ�߳�
								// ��¼�߳���������ر�����ֵ�޸�
								// ���̶߳�����߳��б�������ɾ��
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
						// �ȴ�notEmpty_����
						notEmpty_.wait(lock);
					}
				}

				idleThreadSize_--;

				std::cout << "tid:" << std::this_thread::get_id() << " ��ȡ����ɹ�..." << std::endl;

				// ���������ȡ��һ������
				task = taskQue_.front();
				taskQue_.pop();
				taskSize_--;

				// �����Ȼ��ʣ�����񣬼���֪ͨ�����߳�ִ������
				if (taskQue_.size() > 0) notEmpty_.notify_all();

				// ȡ������󣬽���֪ͨ
				notFull_.notify_all();

			}  // ִ������ǰ�������ͷŵ�������Ӱ�������߳�������ȡ��

			// ��ǰ�̸߳���ִ���������
			if (task != nullptr)
			{
				task();  // ���ô˴��Զ���ɷ���ֵ��ֵ
			}

			idleThreadSize_++;
			lastTime = std::chrono::high_resolution_clock().now();  // �����߳�ִ���������ʱ��
		}
	}

	// ����̳߳�����״̬
	bool checkRunningState() const
	{
		return isPoolRunning_;
	}

private:
	//std::vector<std::unique_ptr<Thread>> threads_;  // �߳��б�
	std::unordered_map<int, std::unique_ptr<Thread>> threads_;  // �߳��б�
	int initThreadSize_;                            // ��ʼ�߳�����
	int threadSizeThreshHold_;                      // �߳�����������ֵ
	std::atomic_int curThreadSize_;                 // ��¼��ǰ�̳߳����߳�������
	std::atomic_int idleThreadSize_;                // ��¼�����߳�����

	// Task����-����������
	using Task = std::function<void()>;          // ���ﲻ��ȷ������ֵ���ͣ�������void����ʵ�ʴ�����ͨ���м���װ�ﵽ��ӦĿ��
	std::queue<Task> taskQue_;                   // �������
	std::atomic_int taskSize_;                   // ��ǰ��������
	int taskQueMaxThreshHold_;                   // ��������������ֵ

	std::mutex taskQueMtx_;             // ��֤��������̰߳�ȫ
	std::condition_variable notFull_;   // ��ʾ������в���
	std::condition_variable notEmpty_;  // ��ʾ������в���
	std::condition_variable exitCond_;  // �ȴ��߳���Դȫ������

	PoolMode poolMode_;  // ��ǰ�̳߳صĹ���ģʽ

	std::atomic_bool isPoolRunning_;  // ��ʾ��ǰ�̳߳ص�����״̬
};

#endif // !THREADPOOL_H
