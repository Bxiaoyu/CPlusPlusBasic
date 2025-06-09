#include <iostream>
#include <vector>
#include "stringhash.h"
#include <string>

using namespace std;

// 布隆过滤器实现
class BloomFilter
{
public:
	BloomFilter(int bitSize = 1471)
		: bitSize_(bitSize)
	{
		bitMap_.resize(bitSize_ / 32 + 1);
	}

public:
	// 添加元素
	void setBit(const char* str)
	{
		// 计算k组哈希函数的值
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;

		// 把相应的idx1,idx2,idx3这几个位置全部置1
		int index = 0;
		int offset = 0;

		index = idx1 / 32;
		offset = idx1 % 32;
		bitMap_[index] |= (1 << offset);

		index = idx2 / 32;
		offset = idx2 % 32;
		bitMap_[index] |= (1 << offset);

		index = idx3 / 32;
		offset = idx3 % 32;
		bitMap_[index] |= (1 << offset);
	}

	// 查询元素
	bool getBit(const char* str)
	{
		// 计算k组哈希函数的值
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;

		int index = 0;
		int offset = 0;

		index = idx1 / 32;
		offset = idx1 % 32;
		if (0 == (bitMap_[index] & (1 << offset)))
		{
			return false;
		}

		index = idx2 / 32;
		offset = idx2 % 32;
		if (0 == (bitMap_[index] & (1 << offset)))
		{
			return false;
		}

		index = idx3 / 32;
		offset = idx3 % 32;
		if (0 == (bitMap_[index] & (1 << offset)))
		{
			return false;
		}

		return true;
	}

private:
	int bitSize_;         // 位图的长度
	vector<int> bitMap_;  // 位图数组
};

// URL黑名单
class BlackList
{
public:
	void add(const string url)
	{
		filter_.setBit(url.c_str());
	}

	bool query(const string url)
	{
		return filter_.getBit(url.c_str());
	}
private:
	BloomFilter filter_;
};

int main()
{
	BlackList list;
	list.add("http://www.baidu.com");
	list.add("http://www.360buy.com");
	list.add("http://www.tmall.com");
	list.add("http://www.tencent.com");

	string url = "http://www.alibaba.com";
	cout << list.query(url) << endl;
}