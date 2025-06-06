#include <iostream>
using namespace std;

/*
* 线性探测哈希表，哈希函数采用除留余数法（尽量选择素数）
*/

// 桶的状态
enum class State
{
	STATE_UNUSE,  // 从未使用过的桶
	STATE_USING,  // 正在使用的桶
	STATE_DEL,    // 元素被删除了的桶
};

// 桶的类型
struct Bucket
{
	Bucket(int key = 0, State state = State::STATE_UNUSE)
		: key_(key)
		, state_(state)
	{
	}

	int key_;      // 存储的数据
	State state_;  // 桶的状态
};

// 哈希表
class HashTable
{
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75)
		: useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		// 把用户传入的size调整到最近的比较大的素数上
		if (size != primes_[0])
		{
			for (;primeIdx_ < PRIME_SIZE; primeIdx_++)
			{
				if (primes_[primeIdx_] >= size)
					break;
			}

			// 如果用户传入的size值过大，已经超过最后一个素数，调整到最后一个素数
			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
		}

		tableSize_ = primes_[primeIdx_];
		table_ = new Bucket[tableSize_];
	}

	~HashTable()
	{
		delete[] table_;
		table_ = nullptr;
	}

public:
	// 插入元素
	bool insert(int key)
	{
		// 考虑扩容
		double loadFactor = useBucketNum_ * 1.0 / tableSize_;
		cout << "current load factor:" << loadFactor << endl;
		if (loadFactor > loadFactor_)
		{
			// 扩容
			expand();
		}

		int idx = key % tableSize_;
		int i = idx;
		do
		{
			if (table_[i].state_ != State::STATE_USING)
			{
				table_[i].state_ = State::STATE_USING;
				table_[i].key_ = key;
				useBucketNum_++;
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (i != idx);

		return false;
	}

	// 删除元素
	bool erase(int key)
	{
		int idx = key % tableSize_;
		int i = idx;

		do
		{
			if (table_[i].state_ == State::STATE_USING && table_[i].key_ == key)
			{
				table_[i].state_ = State::STATE_DEL;
				useBucketNum_--;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != State::STATE_UNUSE && i != idx);  // 如果i的下一个位置状态为UNUSE，则没必要继续循环

		return true;
	}

	// 查询
	bool find(int key)
	{
		int idx = key % tableSize_;
		int i = idx;

		do
		{
			if (table_[i].state_ == State::STATE_USING && table_[i].key_ == key)
			{
				return true;
			}
			i = (i + 1) % tableSize_;
		} while (table_[i].state_ != State::STATE_UNUSE && i != idx);  // 如果i的下一个位置状态为UNUSE，则没必要继续循环

		return false;
	}

private:
	// 扩容函数
	void expand()
	{
		++primeIdx_;
		if (primeIdx_ == PRIME_SIZE)
		{
			throw "HashTable is too large, can not expand anymore!";
		}

		Bucket* newTable = new Bucket[primes_[primeIdx_]];
		for (int i = 0; i < tableSize_; i++)
		{
			// 旧表有效的数据重新哈希放到扩容后的新表
			if (table_[i].state_ == State::STATE_USING)
			{
				int idx = table_[i].key_ % primes_[primeIdx_];

				int k = idx;
				do
				{
					if (newTable[k].state_ != State::STATE_USING)
					{
						newTable[k].state_ = State::STATE_USING;
						newTable[k].key_ = table_[i].key_;
						break;
					}
					k = (k + 1) % primes_[primeIdx_];
				} while (k != idx);
			}
		}

		delete[] table_;
		table_ = newTable;
		tableSize_ = primes_[primeIdx_];
	}

private:
	Bucket* table_;      // 指向动态开辟的哈希表
	int tableSize_;      // 哈希表当前长度
	int useBucketNum_;   // 已经使用的桶个数 
	double loadFactor_;  // 哈希表装载因子

	static const int PRIME_SIZE = 10;  // 素数表的大小
	static int primes_[PRIME_SIZE];    // 素数表
	int primeIdx_;                     // 当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main()
{
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);

	htable.insert(22);

	cout << htable.find(21) << endl;
	htable.erase(21);
	cout << htable.find(21) << endl;
}