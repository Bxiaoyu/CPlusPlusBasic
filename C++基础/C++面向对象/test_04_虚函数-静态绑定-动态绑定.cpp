#include <iostream>
#include <typeinfo>

using namespace std;


/*
* �麯������̬�󶨣���̬��
* 
* һ����������麯�������������ʲôӰ�죿
* �ܽ᣺
* 1.һ�������涨�����麯������ô����׶Σ������������������Ͳ���һ��Ψһ��vftable�麯����
*   �麯��������Ҫ�洢�����ݾ���RTTIָ����麯����ַ������������ʱ��ÿһ���麯����ᱻ���ص�
*   �ڴ��.rodata��ֻ��������
* 
* 2.һ�������涨�����麯������ô����ඨ��Ķ���������ʱ���ڴ��п�ʼ�Ĳ��֣���洢һ��vfptr�麯��ָ��
*   ��ָ����Ӧ���͵��麯����vftable��һ�����Ͷ����n���������ǵ�vfptrָ��Ķ���ͬһ���麯����
* 
* 3.һ���������麯���ĸ�������Ӱ������ڴ�Ĵ�С��vfptr����Ӱ������麯����Ĵ�С��
* 
* 4.����������еķ������ͻ���̳�����ĳ������������ֵ���������������б���ͬ�����һ���ķ�����virtual�麯����
*   ��ô���������������Զ�������麯�������ǵĹ�ϵ���麯�������麯����ַ�ĸ��ǣ���
*/

#if 0
class Base
{
public:
	Base(int data=10):ma(data){}
	virtual void show() { cout << "Base::show()" << endl; }
	virtual void show(int) { cout << "Base::show(int)" << endl; }
protected:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 20) :Base(data), mb(data) {}
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};

int main()
{
	Derive d(50);
	Base* pb = &d;
	/*
	* pb->Base Base::show �������show����ͨ�������ͽ��о�̬��
	* call Base::show (07FF70A7C13F7h)
	* 
	* pb->Base Base::show �������show���麯�����ͽ��ж�̬��
	* mov eax, dword ptr[pb]
	* mov ecx, dword ptr[eax]
	* call ecx(�麯����ַ) ��̬������ʱ�ڣ��İ󶨣��������ã�
	*/
	pb->show();
	pb->show(10);

	cout << sizeof(Base) << endl;    // 4 8
	cout << sizeof(Derive) << endl;  // 8 12

	cout << typeid(pb).name() << endl;  // class Base*

	/*
	* pb�����ͣ�Base -> ��û���麯��
	* ���Baseû���麯����*pbʶ��ľ��Ǳ���ʱ�ڵ����� *pb <=> Base����
	* ���Base���麯����*pbʶ��ľ�������ʱ�ڵ����� RTTI����
	*/
	cout << typeid(*pb).name() << endl; // class Base
	return 0;
}
#endif