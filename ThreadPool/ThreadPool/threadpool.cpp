#include "threadpool.h"

#include <iostream>
#include <chrono>
#include <thread>

const int TASK_MAX_THRESHHOLD = INT32_MAX;
const int THREAD_MAX_THRESHHOLD = 100;
const int THREAD_MAX_IDLE_TIME = 60;  // ��λ:��


ThreadPool::ThreadPool()
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

ThreadPool::~ThreadPool()
{
	isPoolRunning_ = false;

	// �ȴ��̳߳����������̷߳��أ�������״̬������ & ����ִ������
	std::unique_lock<std::mutex> lock(taskQueMtx_);
	notEmpty_.notify_all();
	exitCond_.wait(lock, [&]()->bool {return threads_.size() == 0;});
}

void ThreadPool::setMode(PoolMode mode)
{
	if (checkRunningState()) return;
	poolMode_ = mode;
}

void ThreadPool::setThreadSizeThreshHold(int threshhold)
{
	if (checkRunningState()) return;
	if (poolMode_ != PoolMode::MODE_CACHED) return;
	threadSizeThreshHold_ = threshhold;
}

void ThreadPool::setTaskQueMaxThreshHold(int threshhold)
{
	if (checkRunningState()) return;
	taskQueMaxThreshHold_ = threshhold;
}

Result ThreadPool::submitTask(std::shared_ptr<Task> sp)
{
	// ��ȡ��
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// �̵߳�ͨ�ţ��ȴ���������п���
	// �û��ύ�����������������1s�������ж��ύ����ʧ�ܣ�����
	if (!notFull_.wait_for(lock, std::chrono::seconds(1), 
		[&]()->bool {return taskQue_.size() < taskQueMaxThreshHold_;}))
	{
		// ��ʾnotFull_�ȴ�1s��������Ȼû�����㣬��ʱ����
		std::cerr << "task queue is full, submit task failed." << std::endl;
		return Result(sp, false);
	}

	// ����п��࣬����������������
	taskQue_.emplace(sp);
	taskSize_++;

	// notEmpty_֪ͨ�������߳�ִ������
	notEmpty_.notify_all();

	// cachedģʽ ������ȽϽ��� ������С��������� ��Ҫ�������������Ϳ����߳��������ж��Ƿ���Ҫ�������߳�
	if (poolMode_ == PoolMode::MODE_CACHED && taskSize_ > idleThreadSize_ && curThreadSize_ < threadSizeThreshHold_)
	{
		// �������߳�
		std::cout << ">> create new thread <<<" << std::endl;
		auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
		//threads_.emplace_back(std::move(ptr));
		int threadId = ptr->getId();
		threads_.emplace(threadId, std::move(ptr));
		threads_[threadId]->start();  // �����߳�
		curThreadSize_++;
		idleThreadSize_++;
	}

	// ���������Result����
	return Result(sp);
}

void ThreadPool::start(int initThreadSize)
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

void ThreadPool::threadFunc(int threadId)
{
	auto lastTime = std::chrono::high_resolution_clock().now();

	// �����������ִ���꣬�̳߳زſ��Ի��������߳���Դ
	for (;;)
	{
		std::shared_ptr<Task> task;
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

				// �̳߳�Ҫ�����������߳���Դ
				//if (!isPoolRunning_)
				//{
				//	threads_.erase(threadId);
				//	std::cout << "threadid: " << std::this_thread::get_id() << " exit." << std::endl;
				//	exitCond_.notify_all();
				//	return;  // �����̺߳��������ǽ�����ǰ�߳���
				//}
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
			//task->run();
			task->exec();  // ���ô˴��Զ���ɷ���ֵ��ֵ
		}

		idleThreadSize_++;
		lastTime = std::chrono::high_resolution_clock().now();  // �����߳�ִ���������ʱ��
	}
}

bool ThreadPool::checkRunningState() const
{
	return isPoolRunning_;
}

/*************************************************
* Thread��ʵ��
*************************************************/

int Thread::generateId_ = 0;

Thread::Thread(ThreadFunc func)
	: func_(func)
	, threadId_(generateId_++)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
	// ����һ���̲߳�ִ���̺߳���
	std::thread t(func_, threadId_);
	t.detach();  // ���÷����̣߳��̶߳���������������Ժ�Ӱ���̺߳���ִ��
}

int Thread::getId() const
{
	return threadId_;
}


/*************************************************
* Result��ʵ��
*************************************************/
Result::Result(std::shared_ptr<Task> task, bool isValid)
	: task_(task)
	, isValid_(isValid)
{
	task_->setResult(this);
}

// �߳���ִ��
void Result::setVal(Any any)
{
	// �洢task�ķ���ֵ
	this->any_ = std::move(any);
	sem_.post();  // �Ѿ���ȡ������ķ���ֵ�������ź�����Դ
}

// �û�����
Any Result::get()
{
	if (!isValid_) return "";
	sem_.wait();  // task�������û��ִ���꣬����������û��߳�

	return std::move(any_);
}

/*************************************************
* Task�෽��ʵ��
*************************************************/
Task::Task()
	: result_(nullptr)
{
}

void Task::exec()
{
	if (result_ != nullptr)
	{
		result_->setVal(run());
	}
}

void Task::setResult(Result* res)
{
	result_ = res;
}
