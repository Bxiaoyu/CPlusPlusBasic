#include <iostream>
#include <typeinfo>

using namespace std;

/*
* C++ OOP������� OOP��� thisָ��
* C�����ָ����ĺ������� struct
* C++���� -> ʵ��ĳ�������
* ʵ�壨���ԣ����ģ�-> ADT(abstract data type)
* ���� <- (ʵ����)�ࣨ����->��Ա��������Ϊ->��Ա������
* ��->��Ʒʵ��
* 
* OOP���Ե��Ĵ�������ʲô��
* ����	��װ/����		�̳�		��̬
*/

#if 0
const int NAME_LEN = 20;
// ��Ʒ��������
class CGoods
{
public:
	void init(const char* name, double price, int amount);
	void show();

	// ������ʵ�ֵķ������Զ������inline��������
	void setName(const char* name) { strcpy_s(name_, name); }
	void setPrice(double price) { price_ = price; }
	void setAmount(int amount) { amount_ = amount; }

	const char* getName() { return name_; }
	double getPrice() { return price_; }
	int getAmount() { return amount_; }
private:
	char name_[NAME_LEN];
	double price_;
	int amount_;
};

void CGoods::init(const char* name, double price, int amount)
{
	strcpy_s(name_, name);
	price_ = price;
	amount_ = amount;
}

void CGoods::show()
{
	cout << "name:" << name_ << endl;
	cout << "price:" << price_ << endl;
	cout << "amount:" << amount_ << endl;
}

int main()
{
	// �����ڴ��Сֻ�ͳ�Ա�����й�
	// ��ĳ�Ա����һ�����룬���еķ������������һ��thisָ�룬���յ��ø÷����Ķ���ĵ�ַ
	CGoods goods1;
	// init(&goods1, "���", 10.0, 20)
	goods1.init("���", 10.0, 20);
	// show(&goods1)
	goods1.show();
	goods1.setPrice(10.5);
	goods1.setAmount(15);
	goods1.show();

	return 0;
}
#endif

/*
* ���캯������������
* OOPʵ��һ��˳��ջ
* 
* ���캯������������:
* - ���������ֺ�����һ��
* - û�з���ֵ
* 
* ���캯����
* - �������ʱ�Զ����ã��������أ�������ɣ�����Ͳ�����
* ����������
* - �����������������أ�ֻ��һ������������������ɣ�����Ͳ������ˣ�
* 
* �����ǳ�����������
* - �����Ĭ�Ͽ������캯���������ڴ�Ŀ�����
* - �������ӵ���ⲿ��Դ����ôǳ�����ͻ�������⣻
* - ӵ���ⲿ��Դ�Ķ�����Ҫ�Զ��忽������͸�ֵ���غ���ʵ�����;
*/
#if 0
class SeqStack
{
public:
	// ���Դ���������˿����ṩ������캯�����������캯������
	SeqStack(int size = 10)
	{
		cout << this << " SeqStack()" << endl;
		pstack_ = new int[size];
		top_ = -1;
		size_ = size;
	}

	// �Զ��忽�����캯��
	SeqStack(const SeqStack& other)
	{
		cout << "SeqStack(const SeqStack& other)" << endl;
		pstack_ = new int[other.size_];  // ���
		for (int i = 0; i <= other.top_; ++i)
			pstack_[i] = other.pstack_[i];
		// Ϊʲô����memcpy��������������Ϊ����洢���Ƕ��󣬶��Ҷ���ӵ���ⲿ��Դ����ômemcpy���е���ǳ��������������
		//memcpy(pstack_, other.pstack_, sizeof(int) * other.size_);

		top_ = other.top_;
		size_ = other.size_;
	}

	void operator=(const SeqStack& other)
	{
		// ��ֹ���Ҹ�ֵ
		if (this == &other)
		{
			return;
		}
		cout << "SeqStack& operator=(const SeqStack& other)" << endl;
		delete[] pstack_;  // ��Ҫ���ͷŵ�ǰ����ռ�õ��ⲿ��Դ

		pstack_ = new int[other.size_];
		for (int i = 0; i <= other.top_; ++i)
			pstack_[i] = other.pstack_[i];
		top_ = other.top_;
		size_ = other.size_;
	}

	// ���������ǲ��������ģ�������������ֻ����һ��
	~SeqStack()
	{
		cout << this << " ~SeqStack()" << endl;
		delete[] pstack_;
		pstack_ = nullptr;
	}

	void push(int val)
	{
		if (full())
		{
			resize();
		}
		pstack_[++top_] = val;
	}

	void pop()
	{
		if (empty())
		{
			return;
		}
		--top_;
	}

	int top()
	{
		return pstack_[top_];
	}

	bool empty() { return top_ == -1; }
	bool full() { return top_ == size_ - 1; }
private:
	void resize()
	{
		int* ptmp = new int[size_ * 2];
		for (int i = 0; i < size_; ++i)
		{
			ptmp[i] = pstack_[i];
		}
		delete[] pstack_;
		pstack_ = ptmp;
		size_ *= 2;
	}
private:
	int* pstack_;  // ��̬�������飬�洢˳��ջԪ��
	int top_;  // ջ��Ԫ��λ��
	int size_;  // ���ݴ�С
};

SeqStack gs;  // ȫ�ֺ��������������ʱ������

void test_s1()
{
	SeqStack s;
	//s.init(5);
	for (int i = 0; i < 15; i++)
	{
		s.push(rand() % 100);
	}

	while (!s.empty())
	{
		cout << s.top() << endl;
		s.pop();
	}

	//s.release();

	//SeqStack s1;
	//s1.~SeqStack();  // �����������ú󣬶���Ͳ�������
	//s1.empty();  // ���ڴ�ķǷ�����

	SeqStack* ps = new SeqStack(20);
	ps->push(70);
	ps->push(80);
	ps->pop();
	cout << ps->top() << endl;
	delete ps;  // �ȵ���ps->~SeqStack()+Ȼ��free(ps)
}

int main()
{
	SeqStack s;
	SeqStack s1(10);
	SeqStack s2 = s1;

	s2 = s1;

	return 0;
}
#endif

/*
* ǳ�������Զ��忽�����캯���͸�ֵ���غ���
* ����ʵ����
* - String����
* - ѭ������ Queue
*/

#if 0
// String��
class String
{
public:
	// ��ͨ���캯��
	String(const char* str = nullptr)
	{
		if (str != nullptr)
		{
			data_ = new char[strlen(str) + 1];
			strcpy(data_, str);
		}
		else  // ����û�������ַ�Ϊ�գ�Ҳ����һ���ֽڵĿռ䣬�����������
		{
			data_ = new char[1];
			*data_ = '\0';  // ��Ϊ0
		}
	}

	// �������캯��
	String(const String& other)
	{
		data_ = new char[strlen(other.data_) + 1];
		strcpy(data_, other.data_);
	}

	// ��������
	~String()
	{
		delete[] data_;
		data_ = nullptr;
	}

	// ��ֵ���غ������Ǹ������Ѵ��ڵĶ���ֵ
	// String& ��Ϊ��֧��������operator=����
	String& operator=(const String& other)
	{
		// ��ֹ���Ҹ�ֵ
		if (this == &other)
		{
			return *this;
		}

		delete[] data_;  // �ͷ�ԭ�ȵ���Դ
		data_ = new char[strlen(other.data_) + 1];  // �����¿ռ�
		strcpy(data_, other.data_);

		return *this;
	}
private:
	char* data_;  // ���ڱ����ַ���
};

// ѭ������
class Queue
{
public:
	Queue(int size = 5)
	{
		pQue_ = new int[size];
		front_ = rear_ = 0;
		size_ = size;
	}
	//Queue(const Queue& other) = delete;
	//Queue& operator=(const Queue& other) = delete;
	Queue(const Queue& other)
	{
		size_ = other.size_;
		front_ = other.front_;
		rear_ = other.rear_;
		pQue_ = new int[size_];
		for (int i = front_; i != rear_; i = (i + 1) % size_)
		{
			pQue_[i] = other.pQue_[i];
		}
	}

	Queue& operator=(const Queue& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] pQue_;

		size_ = other.size_;
		front_ = other.front_;
		rear_ = other.rear_;
		pQue_ = new int[size_];
		for (int i = front_; i != rear_; i = (i + 1) % size_)
		{
			pQue_[i] = other.pQue_[i];
		}

		return *this;
	}

	~Queue()
	{
		delete[] pQue_;
		pQue_ = nullptr;
	}

	void push(int val)
	{
		if (full())
		{
			resize();
		}

		pQue_[rear_] = val;
		rear_ = (rear_ + 1) % size_;
	}

	void pop()
	{
		if (empty())
		{
			return;
		}

		front_ = (front_ + 1) % size_;
	}

	int front()
	{
		return pQue_[front_];
	}

	bool full()
	{
		return (rear_ + 1) % size_ == front_;
	}

	bool empty()
	{
		return front_ == rear_;
	}
private:
	void resize()
	{
		int* ptmp = new int[2 * size_];
		int index = 0;
		for (int i = front_; i != rear_; i = (i + 1) % size_)
		{
			ptmp[index++] = pQue_[i];
		}

		delete[] pQue_;
		pQue_ = ptmp;
		front_ = 0;
		rear_ = index;
		size_ *= 2;
	}
private:
	int* pQue_;   // ������е�����ռ�
	int front_;  // ָʾ��ͷλ��
	int rear_;   // ָʾ��βλ��
	int size_;   // �������ݵ��ܴ�С
};

void test_string()
{
	// ���ô���const char* �����Ĺ��캯��
	String s1;
	String s2("Hello");
	String s3 = "world";   // ��ʼ��

	// ���ÿ������캯��
	String s4 = s3;  // ��ʼ��
	String s5(s3);

	// ���ø�ֵ���غ���
	s1 = s2;
}

void test_queue()
{
	Queue q;
	for (int i = 0; i < 20; ++i)
	{
		q.push(rand() % 100);
	}

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;

	Queue q1 = q;
	q1 = q;
}

int main()
{
	//test_string();
	test_queue();
	return 0;
}

#endif

/*
* ���캯���ĳ�ʼ���б�����ָ����ǰ�����Ա�����ĳ�ʼ����ʽ
* ��Ա�����ĳ�ʼ�������Ƕ����˳���йأ��͹��캯����ʼ���б��г��ֵ��Ⱥ�˳���޹أ�
* CDate��CGoods��Ʒ��Ϣ��һ���� a part of... ��Ϲ�ϵ
*/
#if 0
class Test
{
public:
	Test(int data = 10)
		: mb(data)
		, ma(mb)
	{
	}

	void show()
	{
		cout << "ma:" << ma << " mb:" << mb << endl;
	}
private:
	// ��Ա�����ĳ�ʼ�������Ƕ����˳���йأ��͹��캯����ʼ���б��г��ֵ��Ⱥ�˳���޹أ�
	int ma;
	int mb;
};

class CDate
{
public:
	CDate(int year, int month, int day)
	{
		year_ = year;
		month_ = month;
		day_ = day;
	}

	void show()
	{
		cout << year_ << "/" << month_ << "/" << day_ << endl;
	}
private:
	int year_;
	int month_;
	int day_;
};

class CGoods
{
public:
	CGoods(const char* name, int amount, double price, int year, int month, int day)
		: date_(year, month, day)  // ���캯���ĳ�ʼ���б����캯����
		, amount_(amount)
		, price_(price)
	{
		strcpy_s(name_, name);
	}

	void show()
	{
		cout << "name:" << name_ << endl;
		cout << "amount:" << amount_ << endl;
		cout << "price:" << price_ << endl;
		date_.show();
	}
private:
	char name_[20];
	int amount_;
	double price_;
	CDate date_;
};

int main()
{
	CGoods goods("���", 200, 5.0, 2025, 2, 19);
	goods.show();

	Test t;  // -858993460
	t.show();

	return 0;
}
#endif

/*
* ��ĸ��ַ��� - ��Ա����/����
* ��ͨ�ĳ�Ա������-> �����������һ��this�βα���
* 1.�������������
* 2.����ʱ��Ҫ����һ������󣨳������޷����ã�ʵ�Σ�const CGoods* this �βΣ�CGoods* this����
* 3.����������ʶ����˽�г�Ա protected�̳� public private;
* 
* static��̬��Ա������-> ��������this�β�
* 1.�������������
* 2.�����������������÷�����
* 3.����������ʶ����˽�г�Ա�������ڲ���������ĳ�Ա��ֻ�ܵ���������static��̬��Ա��
* 
* const����Ա������-> ���� const CGoods(����)* this
* 1.�������������
* 2.��������һ��������ͨ������ǳ����󶼿��Ե���;
* 3.����������ʶ����˽�г�Ա������ֻ�ܶ���������д��
*/

#if 0
class CDate
{
public:
	CDate(int year, int month, int day)
	{
		year_ = year;
		month_ = month;
		day_ = day;
	}

	// ��ͨ��Ա���� CDate* this
	void show()
	{
		cout << year_ << "/" << month_ << "/" << day_ << endl;
	}

	// ����Ա���� const CDate* this
	void show() const
	{
		cout << year_ << "/" << month_ << "/" << day_ << endl;
	}
private:
	int year_;
	int month_;
	int day_;
};

class CGoods
{
public:
	CGoods(const char* name, int amount, double price, int year, int month, int day)
		: date_(year, month, day)  // ���캯���ĳ�ʼ���б����캯����
		, amount_(amount)
		, price_(price)
	{
		strcpy_s(name_, name);
		count_++;  // ��¼���в������¶��������
	}

	// ��ͨ��Ա���� CGoods* this
	void show()
	{
		cout << "name:" << name_ << endl;
		cout << "amount:" << amount_ << endl;
		cout << "price:" << price_ << endl;
		date_.show();
	}

	// ����Ա���������������ͨshow()���������ع�ϵ
	// ֻҪ��ֻ�������ĳ�Ա������һ��ʵ�ֳ�const����Ա����
	void show() const  // const CGoods* this
	{
		cout << "name:" << name_ << endl;
		cout << "amount:" << amount_ << endl;
		cout << "price:" << price_ << endl;
		date_.show();
	}

	// ��̬��Ա������û��thisָ��
	static void showCGoodsCount()
	{
		cout << "������Ʒ�����������ǣ�" << count_ << endl;
	}
private:
	char name_[20];
	int amount_;
	double price_;
	CDate date_;  // ��Ա���� 1.�����ڴ� 2.���ù��캯��
	static int count_;  // ��̬��Ա���������ڶ��󣬶������༶�𣻼�¼��Ʒ��������
};

// static ��Ա����һ��Ҫ��������ж��岢��ʼ��
int CGoods::count_ = 0;

int main()
{
	CGoods goods1("���1", 200, 5.0, 2025, 2, 19);
	goods1.show();

	CGoods goods2("���2", 200, 5.0, 2025, 2, 19);
	goods2.show();

	CGoods goods3("���3", 200, 5.0, 2025, 2, 19);
	goods3.show();

	CGoods goods4("���4", 200, 5.0, 2025, 2, 19);
	goods4.show();

	// ͳ��������Ʒ��������
	CGoods::showCGoodsCount();

	const CGoods goods5("���5", 200, 5.0, 2025, 2, 19);
	goods5.show();

	return 0;
}
#endif

/*
* ָ�����Ա����Ա�����ͳ�Ա��������ָ��
*/
#if 0
class Test
{
public:
	void func() { cout << "call Test::func" << endl; }
	static void static_func() { cout << "call Test::static_func" << endl; }
	int ma;
	static int mb;
};

int Test::mb;

int main()
{
	Test t1;
	Test *t2 = new Test();

	// ָ���Ա������ָ��
	void (Test::*pfunc)() = &Test::func;
	(t1.*pfunc)();
	(t2->*pfunc)();

	// ָ����static��Ա����
	void(*pfunc1)() = &Test::static_func;
	(*pfunc1)();

#if 0
	// ��ͨ��Ա����
	int Test::* p = &Test::ma;
	t1.*p = 20;
	cout << t1.*p << endl;

	t2->*p = 30;
	cout << t2->*p << endl;

	// ��̬��Ա����
	int* p1 = &Test::mb;
	*p1 = 40;
	cout << *p1 << endl;
#endif

	delete t2;
}
#endif