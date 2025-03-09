#include <iostream>
#include <memory>
#include <string>

using namespace std;


/*
* 适配器模式：让不兼容的接口可以一起工作
* 电脑 -》投影 -》投影仪 VGA HDMI TypeC
* 
* VGA接口的电脑，（TV）投影仪也是VGA
*/
#if 0
class VGA  // VGA接口类
{
public:
	virtual void play() = 0;
};

// TV01表示支持VGA接口的投影仪
class TV01 : public VGA
{
public:
	void play()
	{
		cout << "通过VGA接口进行投影仪播放" << endl;
	}
};

class HDMI
{
public:
	virtual void play() = 0;
};

// 进了一批新的投影仪，但是只支持HDMI接口
class TV02 : public HDMI
{
public:
	void play()
	{
		cout << "通过HDMI接口进行投影仪播放" << endl;
	}
};

// 电脑类（假设只支持VGA接口）
/*
* 如何使用HDMI接口的投影仪呢？
* 方案一：换一个支持HDMI接口的电脑，代码重构
* 方案二：买一个转换头（适配器），将VGA信号转为HDMI信号，这叫添加适配器类
*/
class Computer
{
public:
	// 由于电脑只支持VGA接口，所以该方法参数也只能支持VGA接口的指针/引用
	void playVideo(VGA* pVGA)
	{
		pVGA->play();
	}
};

// 由于电脑（VGA接口）和投影仪（HDMI接口）无法兼容，需要添加适配器类
class VGAToHDMIAdapter : public VGA
{
public:
	VGAToHDMIAdapter(HDMI* p) :phdmi(p) {}

	void play()  // 该方法相当于转换头，做不同接口间的转换
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