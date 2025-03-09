#include <iostream>
#include <memory>

using namespace std;


/*
* ����ģʽ��Proxy����ͨ�������࣬������ʵ�ʶ���ķ���Ȩ��
* �ͻ� -������Proxy��-���ϰ�
*/
#if 0
// 1.������
class VideoSite
{
public:
	virtual void freeMovie() = 0;    // ��ѵ�Ӱ
	virtual void vipMovie() = 0;     // VIP��Ӱ
	virtual void ticketMovie() = 0;  // ��ȯ�ۿ��ĵ�Ӱ
};

// 2.ί����
class FixBugVideoSite : public VideoSite
{
public:
	void freeMovie()
	{
		cout << "�ۿ���ѵ�Ӱ" << endl;
	}

	void vipMovie()
	{
		cout << "�ۿ�VIP��Ӱ" << endl;
	}

	void ticketMovie()
	{
		cout << "��ȯ�ۿ���Ӱ" << endl;
	}
};

// 3.������ ����FixBugVideoSite
class FreeVideoSiteproxy : public VideoSite
{
public:
	FreeVideoSiteproxy() { pVideo = new FixBugVideoSite(); }

	~FreeVideoSiteproxy() { delete pVideo; }

	void freeMovie()
	{
		// ͨ����������freeMovie����������ί��������freeMovie
		pVideo->freeMovie();
	}

	void vipMovie()
	{
		cout << "����Ҫ������VIP�û����ܹۿ�" << endl;
	}

	void ticketMovie()
	{
		cout << "��Ŀǰû�п��õ�Ӱȯ������ȥ����" << endl;
	}
private:
	VideoSite* pVideo;  // 4.���
};

// ������ ����FixBugVideoSite
class VipVideoSiteproxy : public VideoSite
{
public:
	VipVideoSiteproxy() { pVideo = new FixBugVideoSite(); }

	~VipVideoSiteproxy() { delete pVideo; }

	void freeMovie()
	{
		// ͨ����������freeMovie����������ί��������freeMovie
		pVideo->freeMovie();
	}

	void vipMovie()
	{
		// ͨ����������vipMovie����������ί��������vipMovie
		pVideo->vipMovie();
	}

	void ticketMovie()
	{
		cout << "��Ŀǰû�п��õ�Ӱȯ������ȥ����" << endl;
	}
private:
	VideoSite* pVideo;
};

// ��Щ����ͨ�õ�API�ӿڣ�ʹ�õĶ��ǻ����ָ���������
void watchMovie(unique_ptr<VideoSite>& ptr)
{
	ptr->freeMovie();
	ptr->vipMovie();
	ptr->ticketMovie();
}

int main()
{
	unique_ptr<VideoSite> p1(new FreeVideoSiteproxy());  // �ͻ�ֱ�ӷ��ʴ������
	unique_ptr<VideoSite> p2(new VipVideoSiteproxy());
	watchMovie(p1);
	watchMovie(p2);

	return 0;
}
#endif