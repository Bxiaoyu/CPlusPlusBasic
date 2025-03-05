#include <iostream>
#include <memory>

using namespace std;

/*
* ����ָ����ܣ�
* 1���Լ�ʵ������ָ�룻
* 2���������ü���������ָ��auto_ptr(���Ƽ�ʹ��)��scoped_ptr��ʹ�ñȽ��٣���unique_ptr���Ƽ�����
* 3�������ü���������ָ��shared_ptr��weak_ptr��
* 4������ָ��Ľ������ã�ѭ�����ã����⣻
* 5�����̷߳��ʹ���������⣻
* 6���Զ���ɾ������
*/

#if 0
// ʵ�ּ򵥵�����ָ��
// ����ָ�� ��֤������Դ���Զ��ͷ�
// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷ�
template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr)
		: mptr(ptr)
	{
	}

	~CSmartPtr()
	{
		delete mptr;
	}

	T& operator*() { return *mptr; }  // ���ص��ǿ��Ըı��ֵ

	T* operator->() { return mptr; }
private:
	T* mptr;
};

int main()
{
	/*
	* �������ü���������ָ�룬��ν��ǳ�������⣿
	* auto_ptr:C++������ģ����Ƽ�ʹ�ã�ǳ���������������
	* 
	* C++11�±�׼��
	* scoped_ptr����֧�ֿ�������Ϳ�����ֵ�����ܽ��к������κͷ��صȣ�ʹ�ñȽ���
	* - scoped_ptr(const scoped_ptr<T>&) = delete;
	* - scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;
	* 
	* unique_ptr���Ƽ�ʹ��
	* Ҳ��֧����ͨ��������Ϳ������������
	* - unique_ptr(const unique_ptr<T>&) = delete;
	* - unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
	* 
	* �����ṩ�˴���ֵ���ò����Ŀ�������Ϳ������������
	* - unique_ptr(unique_ptr<T>&&);
	* - unique_ptr<T>& operator=(unique_ptr<T>&&);
	*/
	//CSmartPtr<int> ptr(new int(10));

	//auto_ptr<int> ptr1(new int);
	//auto_ptr<int> ptr2(ptr1);
	//*ptr2 = 20;
	//cout << *ptr1 << endl;

	unique_ptr<int> ptr1(new int);
	// std::move -> c++11 ��ֵ���� std::move�õ���ǰ��������ֵ����
	unique_ptr<int> ptr2(std::move(ptr1));
	return 0;
}
#endif