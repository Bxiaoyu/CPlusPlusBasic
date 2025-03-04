#include <iostream>

using namespace std;

/*
* ��ģ�� -��ʵ��һ��C++ STL�����˳������ vector ��������
* ������
* �ռ�������allocator:
* template <class _Ty, class _Alloc = allocator<_Ty>>
* class vector
* 
* �����Ŀռ�������allocator���ļ��£�
* 1.�ڴ濪�٣�
* 2.�ڴ��ͷţ�
* 3.�����죻
* 4.����������
*/

// ���������ռ�����������C++��׼���allocatorʵ��һ��
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size)  // ���𿪱��ڴ�
	{
		return (T*)malloc(sizeof(T) * size);
	}

	void deallocate(void* p)  // �����ͷ��ڴ�
	{
		free(p);
	}

	void construct(T* p, const T& val)   // ���������
	{
		new (p) T(val);  // ��λnew
	}

	void destroy(T* p)  // �����������
	{
		p->~T();  // ~T()����T���͵���������
	}
};

/*
* �����ײ��ڴ濪�٣��ڴ��ͷţ����������������ͨ��allocator�ռ���������ʵ��
*/
template<typename T, typename Alloc = Allocator<T>>
class Vector
{
public:

	Vector(int size = 10)
	{
		// ��Ҫ���ڴ濪�ٺͶ�����ֿ�����
		//first_ = new T[size];
		first_ = allocator_.allocate(size);
		last_ = first_;
		end_ = first_ + size;
	}

	~Vector()
	{
		// ����������Ч��Ԫ�أ�Ȼ���ͷ�first_ָ��ָ��Ķ��ڴ�
		//delete[] first_;
		for (T* p = first_; p != last_; ++p)
		{
			allocator_.destroy(p);  // ��first_ָ��ָ����������ЧԪ�ؽ�����������
		}
		allocator_.deallocate(first_);  // �ͷŶ��ϵ������ڴ�
		first_ = last_ = end_ = nullptr;
	}

	Vector(const Vector<T>& rhs)
	{
		int size = rhs.end_ - rhs.first_;
		//first_ = new T[size];
		first_ = allocator_.allocate(size);
		int len = rhs.last_ - rhs.first_;
		for (int i = 0; i < len; ++i)
		{
			//first_[i] = rhs.first_[i];
			allocator_.construct(first_ + i, rhs.first_[i]);
		}
		last_ = first_ + len;
		end_ = first_ + size;
	}

	Vector<T>& operator=(const Vector<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		//delete[] first_;
		for (T* p = first_; p != last_; ++p)
		{
			allocator_.destroy(p);  // ��first_ָ��ָ����������ЧԪ�ؽ�����������
		}
		allocator_.deallocate(first_);  // �ͷŶ��ϵ������ڴ�

		int size = rhs.end_ - rhs.first_;
		//first_ = new T[size];
		first_ = allocator_.allocate(size);
		int len = rhs.last_ - rhs.first_;
		for (int i = 0; i < len; ++i)
		{
			//first_[i] = rhs.first_[i];
			allocator_.construct(first_ + i, rhs.first_[i]);
		}
		last_ = first_ + len;
		end_ = first_ + size;

		return *this;
	}

	void push_back(const T& val)
	{
		if (full())
		{
			expand();
		}

		//*last_++ = val;  // last_ָ��ָ����ڴ湹��һ��ֵΪval�Ķ���
		allocator_.construct(last_, val);
		last_++;
	}

	void pop_back()
	{
		if (empty())
		{
			return;
		}

		//--last_;  // ����Ҫ��last_ָ��--������Ҫ����ɾ����Ԫ��
		--last_;
		allocator_.destroy(last_);
	}

	T back() const
	{
		if (empty())
		{
			throw "vector is empty!";
		}

		return *(last_ - 1);
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= size())
		{
			throw "OutOfRangeException";
		}
		return first_[index];
	}

	bool full() const { return last_ == end_; }
	bool empty() const { return first_ == last_; }
	int size() const { return last_ - first_; }

	// �ṩ��������������һ��ʵ�ֳ�������Ƕ������
	class iterator
	{
	public:
		iterator(T* p = nullptr) 
			: p_(p)
		{
		}

		bool operator!=(const iterator& it) const
		{
			return p_ != it.p_;
		}

		// ����ǰ��++����������ڶ���һ��ǰ��++Ч�ʸߣ����������ʱ��
		void operator++()
		{
			++p_;
		}

		T& operator*()
		{
			return *p_;
		}
	private:
		T* p_;
	};

	// begin���ص��������ײ���Ԫ�صĵ�������ʾ
	iterator begin()
	{
		return iterator(first_);
	}

	// end���ص�������ĩβԪ�غ��λ�õĵ�������ʾ
	iterator end()
	{
		return iterator(last_);
	}
private:
	void expand()
	{
		int size = end_ - first_;
		//T* ptmp = new T[2 * size];
		T* ptmp = allocator_.allocate(2 * size);
		for (int i = 0; i < size; ++i)
		{
			//ptmp[i] = first_[i];
			allocator_.construct(ptmp + i, first_[i]);
		}

		//delete[] first_;
		for (T* p = first_; p != last_; ++p)
		{
			allocator_.destroy(p);
		}
		allocator_.deallocate(first_);
		first_ = ptmp;
		last_ = first_ + size;
		end_ = first_ + 2 * size;
	}
private:
	T* first_;  // ָ��������ʼ��λ��
	T* last_;   // ָ����������ЧԪ�صĺ��λ��
	T* end_;    // ָ������ռ�ĺ��λ��
	Alloc allocator_;  // ���������Ŀռ�����������
};

class Test
{
public:
	Test() { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test&) { cout << "Test(const Test&)" << endl; }
};

int main()
{
	Vector<int> v1;
	for (int i = 0; i < 20; ++i)
		v1.push_back(rand() % 100);

	//v1.pop_back();

	while (!v1.empty())
	{
		cout << v1.back() << " ";
		v1.pop_back();
	}
	cout << endl;

	cout << "--------------------" << endl;
	Test t1, t2, t3;
	Vector<Test> v2;
	v2.push_back(t1);
	v2.push_back(t2);
	v2.push_back(t3);
	cout << "---------------------" << endl;
	v2.pop_back();  // ֻ��Ҫ��������Ҫ�Ѷ�����������ڴ��ͷŷ��뿪
	cout << "---------------------" << endl;

	Vector<int> v3;
	for (int i = 0;i < 20; ++i)
	{
		v3.push_back(rand() % 100 + 1);
	}

	Vector<int>::iterator it = v3.begin();
	for (;it != v3.end();++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	for (int i = 0; i < v3.size(); ++i)
	{
		cout << v3[i] << " ";
	}
	cout << endl;

	for (int val : v3)  // ��ײ�ԭ������ͨ�������ĵ�������ʵ�������ı���
	{
		cout << val << " ";
	}
	cout << endl;
	return 0;
}