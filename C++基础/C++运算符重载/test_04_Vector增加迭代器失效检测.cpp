#include <iostream>

using namespace std;

/*
* ������ʧЧ�ĵײ�ԭ��ļ����
* ͨ����Vector�������ӵ�����ʧЧ�����ʵ��
*/

#if 0
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

		verify(last_ - 1, last_);
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
		friend class Vector<T, Alloc>;

		iterator(Vector<T, Alloc>* pvec = nullptr, T* p = nullptr)
			: p_(p)
			, pVec_(pvec)
		{
			Iterator_Base* itb = new Iterator_Base(this, pVec_->head_.next_);
			pVec_->head_.next_ = itb;
		}

		bool operator!=(const iterator& it) const
		{
			// ����������Ч��
			if (pVec_ == nullptr || pVec_ != it.pVec_)
			{
				throw "Iterator incompatable!";
			}
			return p_ != it.p_;
		}

		// ����ǰ��++����������ڶ���һ��ǰ��++Ч�ʸߣ����������ʱ��
		void operator++()
		{
			// ����������Ч��
			if (pVec_ == nullptr)
			{
				throw "Iterator invalid!";
			}
			++p_;
		}

		T& operator*()
		{
			if (pVec_ == nullptr)
			{
				throw "Iterator invalid!";
			}
			return *p_;
		}
	private:
		T* p_;
		Vector<T, Alloc>* pVec_;  // ��ǰ����������һ����������
	};

	// begin���ص��������ײ���Ԫ�صĵ�������ʾ
	iterator begin()
	{
		return iterator(this, first_);
	}

	// end���ص�������ĩβԪ�غ��λ�õĵ�������ʾ
	iterator end()
	{
		return iterator(this, last_);
	}

	// �Զ���Vector����insert�����ļ�ʵ��
	iterator insert(iterator it, const T& val)
	{
		/*
		* 1������������
		* 2��������it.p_��ָ��Ϸ���
		*/
		verify(it.p_ - 1, last_);
		T* p = last_;
		while (p > it.p_)
		{
			allocator_.construct(p, *(p - 1));
			allocator_.destroy(p - 1);
			p--;
		}
		allocator_.construct(p, val);
		last_++;
		return iterator(this, p);
	}

	// �Զ���Vector����erase�����ļ�ʵ��
	iterator erase(iterator it)
	{
		verify(it.p_ - 1, last_);
		T* p = it.p_;
		while (p < last_ - 1)
		{
			allocator_.destroy(p);
			allocator_.construct(p, *(p + 1));
			p++;
		}
		allocator_.destroy(p);
		last_--;

		return iterator(this, it.p_);
	}

	// ���������Ƿ�ʧЧ
	void verify(T* first, T* last)
	{
		Iterator_Base* pre = &this->head_;
		Iterator_Base* it = this->head_.next_;
		while (it != nullptr)
		{
			if (it->cur_->p_ > first && it->cur_->p_ <= last_) 
			{
				// ������ʧЧ����iterator���е�����ָ����Ϊnullptr
				it->cur_->pVec_ = nullptr;
				// ɾ����ǰ�������ڵ㣬�����жϺ���ĵ������ڵ��Ƿ�ʧЧ
				pre->next_ = it->next_;
				delete it;
				it = pre->next_;
			}
			else
			{
				pre = it;
				it = it->next_;
			}
		}
	}
private:
	struct Iterator_Base
	{
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			: cur_(c)
			, next_(n)
		{
		}

		iterator* cur_;
		Iterator_Base* next_;
	};

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
	Iterator_Base head_;
};


int main()
{
	Vector<int> vec(200);
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

#if 0
	auto it = vec.begin();
	for (;it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			it = vec.insert(it, *it - 1);
			++it;
		}
	}
#endif

	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	return 0;
}
#endif