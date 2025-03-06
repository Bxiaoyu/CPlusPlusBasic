#include <iostream>
#include <memory>

using namespace std;

/*
* 推荐使用
* unique_ptr -> make_unique
* shared_ptr -> make_shared
* 
* make_shared：
* 此种方式创建智能指针，会把需要托管的内存资源和存储引用计数的内存资源开辟在同一块内存上！
* 
* 优点：
* 1、内存分配效率高，同一块内存资源；
* 2、防止资源泄露的风险；
* 
* 缺点：
* 1、make_shared无法自定义删除器（比如有些是关闭文件资源而不是删除）；
* 2、导致托管的资源延迟释放，即如果还有weak_ptr还在观察（或提升方法），即使引用计数已经为0了，那还不能立即释放资源；
*/

#if 0
class Test
{
public:
	Test(int a) { cout << "Test(int)" << endl; }
	Test(int a, int b) { cout << "Test(int, int)" << endl; }
};

int main()
{
	// 此种方式创建智能指针有问题，会分别创建出资源和引用计数对象两块内存，如果对象生成失败，有内存泄露风险！
	shared_ptr<int> sp1(new int(10));
	shared_ptr<Test> sp2(new Test(10));

	// make_shared方式创建，会把需要托管的内存资源和存储引用计数的内存资源开辟在同一块内存上！
	shared_ptr<int> sp3 = make_shared<int>(10);
	auto sp4 = make_shared<Test>(10);  // new Test(10)
	auto sp5 = make_shared<Test>(10, 20);  // new Test(10,20)
	*sp3 = 20;
	cout << *sp3 << endl;
}
#endif