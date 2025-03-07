#include <iostream>
#include <vector>

using namespace std;

/*
* C++11 STL ����
* ��Ӧ��ǰ��push/insert�������µ�emplace������
* emplace��ֻ�贫�����������Ĳ������ɣ�ֱ���������ײ������ͨ�������ɶ����޶��⿪����
*/

/*
* emplace��ʹ����ʾ
*/
#if 0
class Test
{
public:
	Test() { cout << "Test()" << endl; }
	Test(int a) { cout << "Test(int)" << endl; }
	Test(int a, int b) { cout << "Test(int, int)" << endl; }
	Test(const Test& obj) { cout << "Test(const Test&)" << endl; }
	Test(Test&&) noexcept { cout << "Test(Test&&)" << endl; }
	~Test() { cout << "~Test()" << endl; }
};

// ʵ�������Ŀռ�������
template<typename T>
struct MyAllocator
{
	// allocate deallocate
	T* allocate(size_t size)
	{
		return (T*)malloc(size * sizeof(T));
	}

	void deallocate(void* p)
	{
		cout << "free memory" << endl;
		free(p);
	}

	// construct destroy
	// �����۵��Ӷ��������
	template<typename... Types>
	void construct(T* ptr, Types&&... args)
	{
		// argsֻ��һ�������������Ǹ�Test����TҲ��Test����
		new (ptr) T(std::forward<Types>(args)...);  // ��λnew
	}

	void destroy(T* p)
	{
		p->~T();
	}
};


template<typename T, typename Alloc = MyAllocator<T>>
class Vector
{
public:
	Vector() :vec_(nullptr), size_(0), idx_(0) {}

	~Vector()
	{
		for (int i = 0; i < size_; ++i)
		{
			allocator_.destroy(vec_ + idx_);
			idx_--;
		}
		allocator_.deallocate(vec_);
		vec_ = nullptr;
	}

	// Ԥ���ڴ�ռ�
	void reserve(size_t size)
	{
		vec_ = allocator_.allocate(size);
		size_ = size;
	}

	// push_back
	//void push_back(const T& val)
	//{
	//	allocator_.construct(vec_ + idx_, val);
	//	idx_++;
	//}

	//void push_back(T&& val)
	//{
	//	allocator_.construct(vec_ + idx_, std::move(val));
	//	idx_++;
	//}
	
	// �����۵�����ֵ Type&& val T& val ��ֵ T&& val
	// �򻯴���
	template<typename Type>
	void push_back(Type&& val)
	{
		allocator_.construct(vec_ + idx_, std::forward<Type>(val));
		idx_++;
	}

	// 1�������۵�������ʵ������ֵ������ֵ���Ƶ����β�����ֵ���û�����ֵ����
	template<typename... Types>
	void emplace_back(Types&&... args)
	{
		// ��������ֵ���û�����ֵ���ñ������������Ǹ���ֵ
		// �ڴ��ݵĹ����У�Ҫ����args���������Ͳ��䣨��ֵ�ģ���ֵ�ģ���
		// ʹ��forward����ת��
		allocator_.construct(vec_ + idx_, std::forward<Types>(args)...);
		idx_++;
	}
private:
	T* vec_;
	int size_;
	int idx_;
	Alloc allocator_;
};

int main()
{
	Test t1(10);
	Vector<Test> v;
	v.reserve(10);

	cout << "-----------------" << endl;
	// ֱ�Ӳ�������������Ѿ����ڵĻ�����ʱ���󣩣�����û������
	v.push_back(t1);
	v.emplace_back(t1);
	cout << "-----------------" << endl;
	// ֱ�Ӳ�������������Ѿ����ڵĻ�����ʱ���󣩣�����û������
	v.push_back(Test(20));
	v.emplace_back(Test(20));
	cout << "-----------------" << endl;
	// ��emplace����Test����������Ҫ�Ĳ�����ֱ���������ײ㹹����󼴿ɣ��޶�������
	v.emplace_back(10);
	v.emplace_back(10, 20);
	v.emplace_back();
	cout << "-----------------" << endl;

	/*
	* map<int,string> m;
	* m.insert({10,"Jack"});
	* m.emplace(10, "Jack"); -> ��map�ײ�ֱ�ӵ�����ͨ���캯��������һ��pair���󼴿�
	*/

	return 0;
}
#endif