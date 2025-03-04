#include <iostream>
#include <vector>

using namespace std;

/*
* 迭代器失效问题
* 1、迭代器为什么会失效？
* - 当容器调用erase方法后，当前位置到容器末尾元素的所有迭代器全部失效；
* - 当容器调用insert方法后，当前位置到容器末尾元素的所有迭代器全部失效；
* 
* 迭代器依然有效    -      迭代器全部失效
* 首元素  ---- 插入/删除点 ---- 末尾元素
* 
* - 对insert操作来说，如果引起容器内存扩容，则原来容器的所有迭代器全部失效；
* 
* - 不同容器的迭代器是不能进行比较运算的；
* 
* 2、迭代器失效以后，该怎么解决？
* - 对插入/删除点的迭代器进行更新操作
*/
#if 0
int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

#if 1
	auto it = vec.begin();
	for (;it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			// 这里的迭代器在第一次insert后，就失效了
			it = vec.insert(it, *it - 1);  // 更新迭代器解决失效问题
			++it;
			// break;
		}
	}
#endif

#if 0
	// 把vector容器中所有偶数删除
	auto it = vec.begin();
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			// 迭代器失效问题，第一次调用erase后，迭代器it就失效了
			// 通过更新迭代器来解决失效问题
			it = vec.erase(it);  // 删除的同时更新迭代器
			//break;
		}
		else
		{
			++it;
		}
	}
#endif

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif