#include <iostream>

using namespace std;

/*
* 1���̳еı��ʺ�ԭ��
* 2��������Ĺ������
* 3�����أ����ǣ�����
* 4����̬�󶨺Ͷ�̬��
* 5����̬vfptr��vftable
* 6������������ԭ��
* 7�����ؼ̳��Լ�����
* 8�������vbptr��vbtable
* 9��RTTI
* 10��C++����ǿת����
*/

/*
* 1���̳еı��ʺ�ԭ��
* �̳еı��ʣ�
* a.����ĸ���;
* b.
* 
* �����֮��Ĺ�ϵ��
* a.��ϣ�a part of...  һ���ֵĹ�ϵ
* b.�̳У�a kind of...  һ�ֵĹ�ϵ
* 
* �̳з�ʽ         ����ķ����޶�             ������ķ����޶�           ��main���ⲿ�ķ����޶�
* public          public                   public                    Y
*                 protected                protected                 N
*                 private                  ���ɼ�                     N
* 
* protected       public                   protected                 N
*                 protected                protected                 N
*                 private                  ���ɼ�                     N
* 
* private         public                   private                   N
*                 protected                private                   N
*                 private                  ���ɼ�                     N
* 
* ����ĳ�Ա�ķ����޶��������������ǲ����ܳ����̳з�ʽ��
* 
* �ܽ᣺
* 1.�ⲿֻ�ܷ��ʶ����public��Ա��protected��private�ĳ�Ա�޷�ֱ�ӷ���;
* 2.�ڼ̳нṹ�У�������ӻ�����Լ̳й���private�ĳ�Ա������������ȴ�޷�ֱ�ӷ��ʣ�
* 3.protected��private�������ڻ����ж���ĳ�Ա���뱻��������ʣ����ǲ��뱻�ⲿ���ʣ���ô�ڻ����У�
    ����س�Ա�����protected�����ģ������������ⲿ����������ʣ���ô�ڻ����У��Ͱ���س�Ա�����
	private˽�еģ�

* Ĭ�ϵļ̳з�ʽ��ʲô��
* Ҫ������������class����Ļ���struct����ģ�
* class����������࣬Ĭ�ϼ̳з�ʽ��private�ģ�
* struct����������࣬Ĭ�ϼ̳з�ʽ��public�ģ�
*/

#if 0
class A
{
public:
	int ma;
protected:
	int mb;
private:
	int mc;  // �Լ�������Ԫ�ܷ���˽�г�Ա
};

class B : private A  // �̳� A ����/���� B ������/����
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
	// ����C���棬ma�ķ���Ȩ����ʲô�أ����ɼ��ģ���ΪB��A��private�ļ̳й�ϵ���������ܼ̳���
};


int main()
{
	B b;
	return 0;
}

#endif