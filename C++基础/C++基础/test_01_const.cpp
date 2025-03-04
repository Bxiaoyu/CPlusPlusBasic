#include <iostream>
#include <typeinfo>

using namespace std;

#if 0
int main()
{
	/*
	* C和C++中const的区别是什么？
	*	C++的const必须初始化，叫常量；
	*	C的const可以不初始化，叫常变量;
	* const的编译方式不同：
	*	C中，const是当作一个变量来编译生成指令
	*	C++中，所有出现const常量名字的地方，都被常量的初始化替换了
	*/
	int b = 20;
	//const int a = b;  // 常变量
	const int a = 20; // 常量
	int array[a] = {};
	int* p = (int*) & a;
	*p = 30;

	printf("%d %d %d \n", a, *p, *(&a));
	return 0;
}
#endif