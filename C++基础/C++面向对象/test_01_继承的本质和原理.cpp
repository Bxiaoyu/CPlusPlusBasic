#include <iostream>

using namespace std;

/*
* 1、继承的本质和原理
* 2、派生类的构造过程
* 3、重载，覆盖，隐藏
* 4、静态绑定和动态绑定
* 5、多态vfptr和vftable
* 6、抽象类的设计原理
* 7、多重继承以及问题
* 8、虚基类vbptr和vbtable
* 9、RTTI
* 10、C++四种强转类型
*/

/*
* 1、继承的本质和原理
* 继承的本质：
* a.代码的复用;
* b.
* 
* 类和类之间的关系：
* a.组合：a part of...  一部分的关系
* b.继承：a kind of...  一种的关系
* 
* 继承方式         基类的访问限定             派生类的访问限定           （main）外部的访问限定
* public          public                   public                    Y
*                 protected                protected                 N
*                 private                  不可见                     N
* 
* protected       public                   protected                 N
*                 protected                protected                 N
*                 private                  不可见                     N
* 
* private         public                   private                   N
*                 protected                private                   N
*                 private                  不可见                     N
* 
* 基类的成员的访问限定，在派生类里是不可能超过继承方式的
* 
* 总结：
* 1.外部只能访问对象的public成员，protected和private的成员无法直接访问;
* 2.在继承结构中，派生类从基类可以继承过来private的成员，但是派生类却无法直接访问；
* 3.protected和private的区别？在基类中定义的成员，想被派生类访问，但是不想被外部访问，那么在基类中，
    把相关成员定义成protected保护的；如果派生类和外部都不打算访问，那么在基类中，就把相关成员定义成
	private私有的；

* 默认的继承方式是什么？
* 要看派生类是用class定义的还是struct定义的；
* class定义的派生类，默认继承方式是private的；
* struct定义的派生类，默认继承方式是public的；
*/

#if 0
class A
{
public:
	int ma;
protected:
	int mb;
private:
	int mc;  // 自己或者友元能访问私有成员
};

class B : private A  // 继承 A 基类/父类 B 派生类/子类
{
public:
	void func()
	{
		ma;
		mb;
	}
	int md;
protected:
	int me;
private:
	int mf;
};

class C : public B
{
	// 在类C里面，ma的访问权限是什么呢？不可见的（因为B从A是private的继承关系），但是能继承来
};


int main()
{
	B b;
	return 0;
}

#endif