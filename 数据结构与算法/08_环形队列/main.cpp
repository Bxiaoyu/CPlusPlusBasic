#include <iostream>

using namespace std;

/*
* ���ζ��У�����ʵ�֣�queue  push  pop  front  back  empty size
* ʼ�տճ�һ��λ�ã������ֶ��пջ�����
* first_ == rear_ -> ����Ϊ��
* (rear_ + 1) % length == first_ -> ��������
* rear_����ָ��ĩβԪ�ص���һ��λ��
*/
class Queue
{
public:
	Queue(int size = 10)
		: cap_(size)
		, size_(0)
		, front_(0)
		, rear_(0)
	{
		pQue_ = new int[cap_];
	}

	~Queue()
	{
		delete[] pQue_;
		pQue_ = nullptr;
	}

public:
	// ��� O(1)
	void push(int val)
	{
		if ((rear_ + 1) % cap_ == front_)
		{
			expand(2 * cap_);
		}

		pQue_[rear_] = val;
		rear_ = (rear_ + 1) % cap_;
		size_++;
	}

	// ���� O(1)
	void pop()
	{
		if (rear_ == front_)
			throw "Queue is empty!";
		front_ = (front_ + 1) % cap_;
		size_--;
	}

	// ��ȡ��ͷԪ��
	int front() const
	{
		if (rear_ == front_)
			throw "Queue is empty!";
		return pQue_[front_];
	}

	// ��ȡ��βԪ��
	int back() const
	{
		if (rear_ == front_)
			throw "Queue is empty!";
		// �˴����ǵ�������в��գ���rear_== 0ʱ������ô��ȡ��βԪ��
		// (rear_ - 1 + cap_) % cap_ ��֤ rear_ == 0 ���������ʱҲ����ȷ��ȡ��βԪ��
		return pQue_[(rear_ - 1 + cap_) % cap_];
	}

	// �����п�
	bool empty() const
	{
		return rear_ == front_;
	}

	// ����Ԫ�ظ���
	int size() const
	{
		return size_;
	}

	// ��ӡ
	void show()
	{
		for (int i = front_; i != rear_; i = (i + 1) % cap_)
		{
			cout << pQue_[i] << " ";
		}
		cout << endl;
	}

private:
	// ���ݣ���Ϊ�ǻ��ζ��У�������memcpy���򵥿���
	void expand(int size)
	{
		cout << "expand size..." << endl;
		int* p = new int[size];
		int index = 0;
		for (int i = front_; i != rear_; i = (i + 1) % cap_)
		{
			p[index++] = pQue_[i];
		}
		delete[] pQue_;
		pQue_ = p;
		cap_ = size;
		front_ = 0;
		rear_ = index;
	}
private:
	int* pQue_;
	int front_;  // ��ͷ
	int rear_;   // ��β
	int size_;   // ����Ԫ�ظ���
	int cap_;    // �ռ�����
};

int main()
{
	int arr[] = { 12,4,56,7,89,31,53,75 };
	Queue que;

	for (int v : arr)
	{
		que.push(v);
	}

	que.show();
	cout << que.front() << endl;
	cout << que.back() << endl;

	que.push(100);
	que.push(200);
	que.push(300);
	cout << que.front() << endl;
	cout << que.back() << endl;
	que.show();

	while (!que.empty())
	{
		cout << que.front() << " " << que.back() << endl;
		que.pop();
	}
}