#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

/*
* C++���̱߳�� - �̼߳��ͬ��ͨ�Ż���
* 
* ���̱߳���������⣺
* 1.�̼߳�Ļ���
* ���ھ�̬�����������̳߳���ִ�еĽ����һ�µģ���������CPU���̲߳�ͬ�ĵ���˳�򣬶�������ͬ�����н����
* �������ٽ����������Ҫ��֤ԭ�Ӳ���������ͨ��������mutex����������������ʵ��CAS��
* 
* 2.�̼߳��ͬ��ͨ��
* ������-�������߳�ģ��
* 
* unique_lock��lock_guard��condition_variable
* 1.lock_guard���������ں����������ݻ��߷��ع����У�ֻ�����ڼ򵥵��ٽ�������εĻ�������У�
* 2.unique_lock������ʹ���ڼ򵥵��ٽ�������εĻ�������У�Ҳ�������ں������ù����У�
* 3.condition_variable��wait��notify_one/all������
*/

#if 0
std::mutex mtx;  // ���廥���������̼߳�Ļ������
std::condition_variable cv;  // �����������������̼߳��ͬ��ͨ�Ų�������Ҫ�ͻ�����mutex����ʹ��

// C++ STL�����������������̰߳�ȫ��
class Queue
{
public:
	void put(int val)
	{
		unique_lock<mutex> lck(mtx);
		while (!que.empty())
		{
			// que��Ϊ�գ�Ӧ��֪ͨ������ȥ���ѣ����������ټ�������
			// �������߳�Ӧ�� 1.����ȴ�״̬��2.���Ұ�mtx�������ͷŵ�
			cv.wait(lck);
		}
		que.push(val);
		/*
		* notify_one��֪ͨ�����һ���߳�
		* notify_all��֪ͨ���������߳�
		* �����̵߳õ�֪ͨ�󣬾ͻ�ӵȴ�״̬ -������״̬-���ȴ���ȡ������-��ִ��
		*/
		cv.notify_all();  // ֪ͨ�������߳̿���������
		cout << "������ ������" << val << "����Ʒ" << endl;
	}

	int get()
	{
		unique_lock<mutex> lck(mtx);
		while (que.empty())
		{
			// �������̷߳���que�ǿյģ�֪ͨ�������߳�������Ʒ
			// �������߳̽��� 1.�ȴ�״̬ 2.����mtx�������ͷŵ�
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all();  // ֪ͨ�������߳�����
		cout << "������ ���ѣ�" << val << "����Ʒ" << endl;
		return val;
	}
private:
	queue<int> que;
};


// ����������һ����Ʒ��֪ͨ����������һ�����������ˣ���������֪ͨ�����߼�������
void producer(Queue* q)  // �������߳�
{
	for (int i = 1; i <= 10; ++i)
	{
		q->put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void consumer(Queue* q)  // �������߳�
{
	for (int i = 1; i <= 10; ++i)
	{
		q->get();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	Queue que;  // �̹߳������
	thread t1(producer, &que);
	thread t2(consumer, &que);

	t1.join();
	t2.join();

	return 0;
}
#endif