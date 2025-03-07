#include <iostream>
#include <vector>

using namespace std;

/*
* C++11 STL 容器
* 对应以前的push/insert，增加新的emplace方法；
* emplace：只需传入对象构造所需的参数即可，直接在容器底层调用普通构造生成对象，无额外开销；
*/

/*
* emplace简单使用演示
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

// 实现容器的空间配置器
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
	// 引用折叠加多参数传递
	template<typename... Types>
	void construct(T* ptr, Types&&... args)
	{
		// args只是一个参数，而且是个Test对象，T也是Test类型
		new (ptr) T(std::forward<Types>(args)...);  // 定位new
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

	// 预留内存空间
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
	
	// 引用折叠：左值 Type&& val T& val 右值 T&& val
	// 简化代码
	template<typename Type>
	void push_back(Type&& val)
	{
		allocator_.construct(vec_ + idx_, std::forward<Type>(val));
		idx_++;
	}

	// 1、引用折叠：根据实参是左值还是右值，推导出形参是左值引用还是右值引用
	template<typename... Types>
	void emplace_back(Types&&... args)
	{
		// 不管是左值引用还是右值引用变量，它本身是个左值
		// 在传递的过程中，要保持args的引用类型不变（左值的？右值的？）
		// 使用forward完美转发
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
	// 直接插入对象（无论是已经存在的或是临时对象），二者没有区别
	v.push_back(t1);
	v.emplace_back(t1);
	cout << "-----------------" << endl;
	// 直接插入对象（无论是已经存在的或是临时对象），二者没有区别
	v.push_back(Test(20));
	v.emplace_back(Test(20));
	cout << "-----------------" << endl;
	// 给emplace传入Test对象构造所需要的参数，直接在容器底层构造对象即可，无额外消耗
	v.emplace_back(10);
	v.emplace_back(10, 20);
	v.emplace_back();
	cout << "-----------------" << endl;

	/*
	* map<int,string> m;
	* m.insert({10,"Jack"});
	* m.emplace(10, "Jack"); -> 在map底层直接调用普通构造函数，生成一个pair对象即可
	*/

	return 0;
}
#endif