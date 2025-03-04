#include <iostream>
#include <typeinfo>

using namespace std;

/*
* ����һ����Щ��������ʵ�ֳ��麯����
* �������麯��������
* 1.�麯���ܲ�����ַ���洢��vftable�У�
* 2.���������ڣ�vfptr->vftable->�麯����ַ����
* 
* ���캯�� NO
* 1.virtual+���캯�� NO!
* 2.���캯���У����õ��κκ��������Ǿ�̬�󶨣������麯����Ҳ���ᷢ����̬�󶨣�
* 3.�����๹����̣��ȵ��û��๹�죬Ȼ����������๹�죻
* 
* static��̬��Ա���� NO
* 1.��̬��Ա��������������
* 
* �����������������
* 1.�����������Զ���Ϊ�麯������Ϊ�����������õ�ʱ�򣬶����Ǵ��ڵģ�
* 2.����������������麯������ô����������������Զ���Ϊ�麯����
* 
* ��������ʲôʱ������������������ʵ�ֳ�������������
* �����ָ�루���ã�ָ�����new����������������ʱ��delete pb(����ָ��),
* ����������������ʱ�򣬱��뷢����̬�󶨣�����ᵼ������������������޷����ã�
*/

#if 0
class Base
{
public:
	Base(int data = 10) :ma(data) 
	{
		cout << "Base()" << endl;
	}

	virtual ~Base()
	{
		cout << "~Base()" << endl;
	}

	virtual void show()
	{
		cout << "Call Base::show()" << endl;
	}
private:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data)
		: Base(data)
		, mb(data)
		, ptr(new int(data))
	{
		cout << "Derive()" << endl;
	}

	~Derive()
	{
		delete ptr;
		ptr = nullptr;
		cout << "~Derive()" << endl;
	}
private:
	int mb;
	int* ptr;
};

int main()
{
	Base* pb = new Derive(10);
	pb->show();  // ��̬�� pb Base* *pb Derive
	delete pb;  // û�ж��������������ʱ�����������������û�б����õ�������

	/*
	* pb->Base Base::~Base �������������ĵ��ã����Ǿ�̬��
	* call Base::~Base()
	* 
	* ������������������Ϊ��������
	* pb->Base Base::~Base �������������ĵ��ã����Ƕ�̬����
	* pb->Derive Derive vftable &Derive::~Derive
	*/

	/*
	Derive d(10);
	Base* pb = &d;
	pb->show();
	*/
	return 0;
}
#endif