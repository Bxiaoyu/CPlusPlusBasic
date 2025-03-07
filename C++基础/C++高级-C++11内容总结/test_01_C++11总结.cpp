#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>  // �����ܶ�ԭ������
#include <list>

using namespace std;

/*
* C++11��׼��������ܽ᣺
* 
* һ���ؼ��ֺ��﷨��
* 1.auto�����Ը�����ֵ�Ƶ�����ֵ�����ͣ�Ȼ����߱���������Ҳ��֪���ˣ�
* 2.nullptr����ָ��ר�ã��ܹ��������������𣩡��ϵ�NULL -�� #define NULL 0��
* 3.foreach�����Ա������飬�����ȣ�
*	for(Type val : container)  // �ײ����ͨ��ָ����ߵ�������ʵ��
*	{
*		cout << val << " ";
*	}
* 
* 4.��ֵ���ã�move�ƶ����庯����forward��������ת���������ܶԶ�����Ż���ܴ����ã�
* 5.ģ���һ�������ԣ�typename... A  ��ʾ�ɱ�Σ����Ͳ�������
* 
* ���������ͺ�������
* 1.function����������
* 2.bind����������ԭ��STL��bind1st��bind2nd��������
* 3.lambda���ʽ��
* 
* ��������ָ�룺
* 1.shared_ptr��weak_ptr��
* 
* �ġ�����������
* ԭ��ֻ��set��map��ͨ�������ʵ�֣�����
* 1.unordered_set��unordered_map��ͨ����ϣ��ʵ�֣����� ��ɾ��O(1)��
* 2.array�����飨��֧�ֶ�̬���ݣ���ԭ��ֻ��vector��
* 3.forward_list��ǰ������ԭ��ֻ��list��˫��ѭ��������
* 
* �塢C++���Լ���֧�ֵĶ��̱߳�̣����Կ�ƽ̨����
* 1.thread���߳��ࣻ
* 2.mutex����������
* 3.condition_variable������������
* 4.lock_guard��unique_lock������ָ�����͵ļ���������
* 5.atomic��ԭ�����ͣ�����CAS������ԭ�����ͣ��̰߳�ȫ��
* 6.sleep_for��
* �ȡ�
* 
* C++���Բ��� thread
* Windows              linux
*	 |                    |
* createThread       pthread_create
*/


/*
* �߳����ݣ�
* һ����δ���������һ���̣߳�
* std::thread����һ���̶߳��󣬴����߳�������̺߳����Ͳ������߳��Զ�������
* 
* �������߳���ν�����
* ���̺߳���������ɣ��߳̾ͽ�����
* 
* �������߳���δ������̣߳�
* 1��t.join()���ȴ�t�߳̽�������ǰ�̼߳����������У�
* 2��t.detach()��t�߳�����Ϊ�����̣߳����߳̽������������̽������������̶߳��Զ������ˣ�
*/
#if 0
void threadHandle1(int time)
{
	// �����߳�˯������
	this_thread::sleep_for(std::chrono::seconds(time));
	cout << this_thread::get_id() << " hello thread!" << endl;
}

int main()
{
	// ����һ���̶߳��󣬴���һ���̺߳��������߳̾Ϳ�ʼ������
	thread t1(threadHandle1, 2);
	thread t2(threadHandle1, 3);
	// ���̵߳ȴ����߳̽��������̼߳�����������
	t1.join();
	t2.join();
	// �����߳�����Ϊ�����߳�
	//t1.detach();

	cout << "Main thread done." << endl;

	/*
	* ���߳�������ɣ��鿴�����ǰ���̻���δ������ɵ����̣߳����̾ͻ��쳣��ֹ
	*/

	return 0;
}
#endif

/*
* ���̳߳���
* ��̬���������̳߳���ִ�еĽ����һ�µģ���������CPU���̲߳�ͬ�ĵ���˳�򣬶�������ͬ�����н����
* 
* ʹ�û����������̬����ʾ����
* ģ�⳵վ����������Ʊ����
*/

#if 0
int ticketCount = 100; // ��վ��100�ų�Ʊ������������һ����Ʊ
std::mutex mtx;  // ȫ�ֻ�����

// ģ����Ʊ�̺߳���
void sellTicket(int index)
{
	while (ticketCount > 0)  // ticketCount = 1 ��+˫���ж�
	{
		{
			//std::unique_lock<std::mutex> lock(mtx);
			std::lock_guard<std::mutex> lock(mtx);
			if (ticketCount > 0)
			{
				// �ٽ�������Σ�����ԭ�Ӳ������̼߳以��
				cout << "���ڣ�" << index << "�����ڣ�" << ticketCount << "��Ʊ." << endl;
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

	cout << "���д�����Ʊ������" << endl;
	return 0;
}
#endif

/*
* ʹ��ԭ�����ʹ��滥��������򵥾�̬����
* ԭ���û�����ʵ�֣�
* lock_guard<mutex> lock(mtx);
* count++;
* 
* lock_guard<mutex> lock(mtx);
* count--;
* 
* �������ǱȽ��صģ��ٽ������������������Ը��ӣ���
* ϵͳ���ۣ�CAS��֤����++��--������ԭ�����Ծ��㹻�ˣ���������
*          exchange/swap  �������� -��CAS��ʵ�ֵ�
*/
#if 0
// volatile�ؼ��֣���ֹ������������̻߳��棬��֤�̷߳��ʵĶ��Ǳ���ԭʼ�ڴ�����
// ��Ȼ�����кô���������ʱ��Ҳ������鷳
volatile std::atomic_bool isReady = false;
volatile std::atomic_int _count = 0;

void task()
{
	while (!isReady)
	{
		std::this_thread::yield();  // �̳߳��õ�ǰ��CPUʱ��Ƭ���ȴ���һ�ε���
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