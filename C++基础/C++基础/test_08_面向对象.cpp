#include <iostream>
#include <typeinfo>

using namespace std;

/*
* C++ OOP面向对象 OOP编程 this指针
* C：各种各样的函数定义 struct
* C++：类 -> 实体的抽象类型
* 实体（属性，行文）-> ADT(abstract data type)
* 对象 <- (实例化)类（属性->成员变量，行为->成员方法）
* 类->商品实体
* 
* OOP语言的四大特征是什么？
* 抽象	封装/隐藏		继承		多态
*/

#if 0
const int NAME_LEN = 20;
// 商品抽象类型
class CGoods
{
public:
	void init(const char* name, double price, int amount);
	void show();

	// 类体内实现的方法，自动处理成inline内联函数
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
	// 对象内存大小只和成员变量有关
	// 类的成员方法一经编译，所有的方法参数都会加一个this指针，接收调用该方法的对象的地址
	CGoods goods1;
	// init(&goods1, "面包", 10.0, 20)
	goods1.init("面包", 10.0, 20);
	// show(&goods1)
	goods1.show();
	goods1.setPrice(10.5);
	goods1.setAmount(15);
	goods1.show();

	return 0;
}
#endif

/*
* 构造函数和析构函数
* OOP实现一个顺序栈
* 
* 构造函数和析构函数:
* - 函数的名字和类名一样
* - 没有返回值
* 
* 构造函数：
* - 定义对象时自动调用，可以重载，构造完成，对象就产生；
* 析构函数：
* - 不带参数，不能重载，只有一个析构函数，析构完成，对象就不存在了；
* 
* 对象的浅拷贝和深拷贝：
* - 对象的默认拷贝构造函数做的是内存的拷贝；
* - 如果对象拥有外部资源，那么浅拷贝就会出现问题；
* - 拥有外部资源的对象需要自定义拷贝构造和赋值重载函数实现深拷贝;
*/
#if 0
class SeqStack
{
public:
	// 可以带参数，因此可以提供多个构造函数，叫做构造函数重载
	SeqStack(int size = 10)
	{
		cout << this << " SeqStack()" << endl;
		pstack_ = new int[size];
		top_ = -1;
		size_ = size;
	}

	// 自定义拷贝构造函数
	SeqStack(const SeqStack& other)
	{
		cout << "SeqStack(const SeqStack& other)" << endl;
		pstack_ = new int[other.size_];  // 深拷贝
		for (int i = 0; i <= other.top_; ++i)
			pstack_[i] = other.pstack_[i];
		// 为什么不用memcpy函数来拷贝，因为如果存储的是对象，而且对象拥有外部资源，那么memcpy进行的是浅拷贝，会有问题
		//memcpy(pstack_, other.pstack_, sizeof(int) * other.size_);

		top_ = other.top_;
		size_ = other.size_;
	}

	void operator=(const SeqStack& other)
	{
		// 防止自我赋值
		if (this == &other)
		{
			return;
		}
		cout << "SeqStack& operator=(const SeqStack& other)" << endl;
		delete[] pstack_;  // 需要先释放当前对象占用的外部资源

		pstack_ = new int[other.size_];
		for (int i = 0; i <= other.top_; ++i)
			pstack_[i] = other.pstack_[i];
		top_ = other.top_;
		size_ = other.size_;
	}

	// 析构函数是不带参数的，而且析构函数只能有一个
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
	int* pstack_;  // 动态开辟数组，存储顺序栈元素
	int top_;  // 栈顶元素位置
	int size_;  // 扩容大小
};

SeqStack gs;  // 全局函数，程序结束的时候析构

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
	//s1.~SeqStack();  // 析构函数调用后，对象就不存在了
	//s1.empty();  // 堆内存的非法访问

	SeqStack* ps = new SeqStack(20);
	ps->push(70);
	ps->push(80);
	ps->pop();
	cout << ps->top() << endl;
	delete ps;  // 先调用ps->~SeqStack()+然后free(ps)
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
* 浅拷贝：自定义拷贝构造函数和赋值重载函数
* 代码实践：
* - String类型
* - 循环队列 Queue
*/

#if 0
// String类
class String
{
public:
	// 普通构造函数
	String(const char* str = nullptr)
	{
		if (str != nullptr)
		{
			data_ = new char[strlen(str) + 1];
			strcpy(data_, str);
		}
		else  // 如果用户传入的字符为空，也生成一个字节的空间，方便后续处理
		{
			data_ = new char[1];
			*data_ = '\0';  // 置为0
		}
	}

	// 拷贝构造函数
	String(const String& other)
	{
		data_ = new char[strlen(other.data_) + 1];
		strcpy(data_, other.data_);
	}

	// 析构函数
	~String()
	{
		delete[] data_;
		data_ = nullptr;
	}

	// 赋值重载函数，是给两个已存在的对象赋值
	// String& 是为了支持连续的operator=操作
	String& operator=(const String& other)
	{
		// 防止自我赋值
		if (this == &other)
		{
			return *this;
		}

		delete[] data_;  // 释放原先的资源
		data_ = new char[strlen(other.data_) + 1];  // 开辟新空间
		strcpy(data_, other.data_);

		return *this;
	}
private:
	char* data_;  // 用于保存字符串
};

// 循环队列
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
	int* pQue_;   // 申请队列的数组空间
	int front_;  // 指示队头位置
	int rear_;   // 指示队尾位置
	int size_;   // 队列扩容的总大小
};

void test_string()
{
	// 调用带有const char* 参数的构造函数
	String s1;
	String s2("Hello");
	String s3 = "world";   // 初始化

	// 调用拷贝构造函数
	String s4 = s3;  // 初始化
	String s5(s3);

	// 调用赋值重载函数
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
* 构造函数的初始化列表：可以指定当前对象成员变量的初始化方式
* 成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关！
* CDate是CGoods商品信息的一部分 a part of... 组合关系
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
	// 成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关！
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
		: date_(year, month, day)  // 构造函数的初始化列表，构造函数的
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
	CGoods goods("面包", 200, 5.0, 2025, 2, 19);
	goods.show();

	Test t;  // -858993460
	t.show();

	return 0;
}
#endif

/*
* 类的各种方法 - 成员方法/变量
* 普通的成员方法：-> 编译器会添加一个this形参变量
* 1.属于类的作用域；
* 2.调用时需要依赖一个类对象（常对象无法调用，实参：const CGoods* this 形参：CGoods* this）；
* 3.可以任意访问对象的私有成员 protected继承 public private;
* 
* static静态成员方法：-> 不会生成this形参
* 1.属于类的作用域；
* 2.用类名作用域来调用方法；
* 3.可以任意访问对象的私有成员，仅限于不依赖对象的成员（只能调用其它的static静态成员）
* 
* const常成员方法：-> 生成 const CGoods(类型)* this
* 1.属于类的作用域；
* 2.调用依赖一个对象，普通对象或是常对象都可以调用;
* 3.可以任意访问对象的私有成员，但是只能读，而不能写；
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

	// 普通成员方法 CDate* this
	void show()
	{
		cout << year_ << "/" << month_ << "/" << day_ << endl;
	}

	// 常成员方法 const CDate* this
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
		: date_(year, month, day)  // 构造函数的初始化列表，构造函数的
		, amount_(amount)
		, price_(price)
	{
		strcpy_s(name_, name);
		count_++;  // 记录所有产生的新对象的数量
	}

	// 普通成员方法 CGoods* this
	void show()
	{
		cout << "name:" << name_ << endl;
		cout << "amount:" << amount_ << endl;
		cout << "price:" << price_ << endl;
		date_.show();
	}

	// 常成员方法，与上面的普通show()方法是重载关系
	// 只要是只读操作的成员方法，一律实现成const常成员方法
	void show() const  // const CGoods* this
	{
		cout << "name:" << name_ << endl;
		cout << "amount:" << amount_ << endl;
		cout << "price:" << price_ << endl;
		date_.show();
	}

	// 静态成员方法，没有this指针
	static void showCGoodsCount()
	{
		cout << "所有商品的种类数量是：" << count_ << endl;
	}
private:
	char name_[20];
	int amount_;
	double price_;
	CDate date_;  // 成员对象 1.分配内存 2.调用构造函数
	static int count_;  // 静态成员变量不属于对象，而属于类级别；记录商品对象总数
};

// static 成员变量一定要在类外进行定义并初始化
int CGoods::count_ = 0;

int main()
{
	CGoods goods1("面包1", 200, 5.0, 2025, 2, 19);
	goods1.show();

	CGoods goods2("面包2", 200, 5.0, 2025, 2, 19);
	goods2.show();

	CGoods goods3("面包3", 200, 5.0, 2025, 2, 19);
	goods3.show();

	CGoods goods4("面包4", 200, 5.0, 2025, 2, 19);
	goods4.show();

	// 统计所有商品的总数量
	CGoods::showCGoodsCount();

	const CGoods goods5("面包5", 200, 5.0, 2025, 2, 19);
	goods5.show();

	return 0;
}
#endif

/*
* 指向类成员（成员变量和成员方法）的指针
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

	// 指向成员方法的指针
	void (Test::*pfunc)() = &Test::func;
	(t1.*pfunc)();
	(t2->*pfunc)();

	// 指向类static成员方法
	void(*pfunc1)() = &Test::static_func;
	(*pfunc1)();

#if 0
	// 普通成员变量
	int Test::* p = &Test::ma;
	t1.*p = 20;
	cout << t1.*p << endl;

	t2->*p = 30;
	cout << t2->*p << endl;

	// 静态成员变量
	int* p1 = &Test::mb;
	*p1 = 40;
	cout << *p1 << endl;
#endif

	delete t2;
}
#endif