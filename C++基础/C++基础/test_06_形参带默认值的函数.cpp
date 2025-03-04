#include <iostream>
#include <typeinfo>

using namespace std;

/*
* 形参带默认值的函数
* 1.给默认值的时候，从右向左给；
* 2.调用效率的问题；
* 3.函数定义处可以给形参默认值，声明处也可以给形参默认值；
* 4.形参给默认值的时候，不管是定义处给还是声明处给，形参默认值只能出现一次；
*/

#if 0
int sum(int a, int b = 20);  // 声明时定义参数默认值

int sum(int a=10, int b = 20)  // 定义处给参数默认值
{
	return a + b;
}

int main()
{
	int a = 30;
	int b = 40;

	int ret = sum(a, b);
	cout << "ret:" << ret << endl;

	ret = sum(a);
	cout << "ret:" << ret << endl;

	ret = sum();
	cout << "ret:" << ret << endl;
}

#endif