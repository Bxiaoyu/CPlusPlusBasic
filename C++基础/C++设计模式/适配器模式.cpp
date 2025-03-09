#include <iostream>
#include <memory>
#include <string>

using namespace std;


/*
* ������ģʽ���ò����ݵĽӿڿ���һ����
* ���� -��ͶӰ -��ͶӰ�� VGA HDMI TypeC
* 
* VGA�ӿڵĵ��ԣ���TV��ͶӰ��Ҳ��VGA
*/
#if 0
class VGA  // VGA�ӿ���
{
public:
	virtual void play() = 0;
};

// TV01��ʾ֧��VGA�ӿڵ�ͶӰ��
class TV01 : public VGA
{
public:
	void play()
	{
		cout << "ͨ��VGA�ӿڽ���ͶӰ�ǲ���" << endl;
	}
};

class HDMI
{
public:
	virtual void play() = 0;
};

// ����һ���µ�ͶӰ�ǣ�����ֻ֧��HDMI�ӿ�
class TV02 : public HDMI
{
public:
	void play()
	{
		cout << "ͨ��HDMI�ӿڽ���ͶӰ�ǲ���" << endl;
	}
};

// �����ࣨ����ֻ֧��VGA�ӿڣ�
/*
* ���ʹ��HDMI�ӿڵ�ͶӰ���أ�
* ����һ����һ��֧��HDMI�ӿڵĵ��ԣ������ع�
* ����������һ��ת��ͷ��������������VGA�ź�תΪHDMI�źţ���������������
*/
class Computer
{
public:
	// ���ڵ���ֻ֧��VGA�ӿڣ����Ը÷�������Ҳֻ��֧��VGA�ӿڵ�ָ��/����
	void playVideo(VGA* pVGA)
	{
		pVGA->play();
	}
};

// ���ڵ��ԣ�VGA�ӿڣ���ͶӰ�ǣ�HDMI�ӿڣ��޷����ݣ���Ҫ�����������
class VGAToHDMIAdapter : public VGA
{
public:
	VGAToHDMIAdapter(HDMI* p) :phdmi(p) {}

	void play()  // �÷����൱��ת��ͷ������ͬ�ӿڼ��ת��
	{
		phdmi->play();
	}
private:
	HDMI* phdmi;
};

int main()
{
	Computer computer;
	//computer.playVideo(new TV01());
	computer.playVideo(new VGAToHDMIAdapter(new TV02()));

	return 0;
}
#endif