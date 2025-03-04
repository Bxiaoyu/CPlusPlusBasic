#include <iostream>
#include <typeinfo>

using namespace std;

/*
* �麯���Ͷ�̬��
* 
* ����һ���ǲ����麯���ĵ���һ���Ƕ�̬�󶨣�
* 1.���ǵģ���������Ĺ��캯���е����麯�����Ǿ�̬�󶨣����캯���е��������������飩�����ᷢ����̬�󶨣���
* 2.�������ͨ��ָ��������ñ����������麯�����Ǿ��Ǿ�̬�󶨣�
*/

#if 0
class Base
{
public:
	Base(int data = 0) :ma(data) {}
	virtual void show() { cout << "Base::show()" << endl; }
protected:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 0) :Base(data), mb(data) {}
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};

int main()
{
	Base b;
	Derive d;

	// ��̬�� �ö���������麯�����Ǿ�̬��
	b.show();  // �麯�� call Base::show
	d.show();  // �麯�� call Derive::show

	// ��̬�� ������ָ������õ����麯��
	Base* pb1 = &b;
	pb1->show();
	Base* pb2 = &d;
	pb2->show();
	
	// ��̬��
	Base& rb1 = b;
	rb1.show();
	Base& rb2 = d;
	rb2.show();

	Derive* pd2 = (Derive*)&b;
	pd2->show();  // ��̬�� pd2->b vfptr -> Base vftable Base::show

	return 0;
}
#endif