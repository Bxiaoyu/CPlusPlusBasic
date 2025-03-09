#include <iostream>
#include <memory>

using namespace std;


/*
* 代理模式（Proxy）：通过代理类，来控制实际对象的访问权限
* 客户 -》助理（Proxy）-》老板
*/
#if 0
// 1.抽象类
class VideoSite
{
public:
	virtual void freeMovie() = 0;    // 免费电影
	virtual void vipMovie() = 0;     // VIP电影
	virtual void ticketMovie() = 0;  // 用券观看的电影
};

// 2.委托类
class FixBugVideoSite : public VideoSite
{
public:
	void freeMovie()
	{
		cout << "观看免费电影" << endl;
	}

	void vipMovie()
	{
		cout << "观看VIP电影" << endl;
	}

	void ticketMovie()
	{
		cout << "用券观看电影" << endl;
	}
};

// 3.代理类 代理FixBugVideoSite
class FreeVideoSiteproxy : public VideoSite
{
public:
	FreeVideoSiteproxy() { pVideo = new FixBugVideoSite(); }

	~FreeVideoSiteproxy() { delete pVideo; }

	void freeMovie()
	{
		// 通过代理对象的freeMovie，访问真正委托类对象的freeMovie
		pVideo->freeMovie();
	}

	void vipMovie()
	{
		cout << "您需要升级成VIP用户才能观看" << endl;
	}

	void ticketMovie()
	{
		cout << "您目前没有可用电影券，请先去购买" << endl;
	}
private:
	VideoSite* pVideo;  // 4.组合
};

// 代理类 代理FixBugVideoSite
class VipVideoSiteproxy : public VideoSite
{
public:
	VipVideoSiteproxy() { pVideo = new FixBugVideoSite(); }

	~VipVideoSiteproxy() { delete pVideo; }

	void freeMovie()
	{
		// 通过代理对象的freeMovie，访问真正委托类对象的freeMovie
		pVideo->freeMovie();
	}

	void vipMovie()
	{
		// 通过代理对象的vipMovie，访问真正委托类对象的vipMovie
		pVideo->vipMovie();
	}

	void ticketMovie()
	{
		cout << "您目前没有可用电影券，请先去购买" << endl;
	}
private:
	VideoSite* pVideo;
};

// 这些都是通用的API接口，使用的都是基类的指针或者引用
void watchMovie(unique_ptr<VideoSite>& ptr)
{
	ptr->freeMovie();
	ptr->vipMovie();
	ptr->ticketMovie();
}

int main()
{
	unique_ptr<VideoSite> p1(new FreeVideoSiteproxy());  // 客户直接访问代理对象
	unique_ptr<VideoSite> p2(new VipVideoSiteproxy());
	watchMovie(p1);
	watchMovie(p2);

	return 0;
}
#endif