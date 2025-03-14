#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
* �����Ŀ����ʵ�������෽������ɴ����ӷ�
*/
#if 0
class BigInt
{
public:
	BigInt(string str) : strDigit(str) {}
private:
	friend ostream& operator<<(ostream& out, const BigInt& src);
	friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);
	friend BigInt operator-(const BigInt& lhs, const BigInt& rhs);
private:
	string strDigit;  // ʹ���ַ����洢������
};

ostream& operator<<(ostream& out, const BigInt& src)
{
	out << src.strDigit;
	return out;
}

// �����ӷ�
BigInt operator+(const BigInt& lhs, const BigInt& rhs)
{
	/*
	* �����ַ���l,r���Ӻ���ǰ����
	* ͬλ�õ�������ӣ���λflag ����һ��������� string result
	* ͬʱ���
	* ĳ���ַ�������ɣ���Ҫ���ǽ�λ
	*/
	string result;
	bool flag = false;
	int i = lhs.strDigit.length() - 1;
	int j = rhs.strDigit.length() - 1;

	for (;i >= 0 && j >= 0; --i, --j)
	{
		/*
		* ��ASCII�����У��ַ�ʵ���϶�Ӧһ�����֡����磬�ַ�'0'��ASCIIֵ��48���ַ�'1'��ASCIIֵ��49���������ơ�
		* �����ͨ����ȥ'0'��ASCIIֵ���õ�һ�����֡�
		*/
		int ret = lhs.strDigit[i] - '0' + rhs.strDigit[j] - '0';
		if (flag)
		{
			ret += 1;
			flag = false;
		}

		if (ret >= 10)
		{
			ret %= 10;  // ȡ����
			flag = true;
		}

		result.push_back(ret + '0');
	}

	// �ж� i,j �Ƿ񻹴���0
	if (i >= 0)
	{
		while (i >= 0)
		{
			int ret = lhs.strDigit[i] - '0';
			if (flag)
			{
				ret += 1;
				flag = false;
			}

			if (ret >= 10)
			{
				ret %= 10;
				flag = true;
			}
			result.push_back(ret + '0');
			i--;
		}
	}
	else if (j >= 0)
	{
		while (j >= 0)
		{
			int ret = rhs.strDigit[j] - '0';
			if (flag)
			{
				ret += 1;
				flag = false;
			}

			if (ret >= 10)
			{
				ret %= 10;
				flag = true;
			}
			result.push_back(ret + '0');
			j--;
		}
	}

	if (flag)
	{
		result.push_back('1');
	}

	reverse(result.begin(), result.end());  // ��ת�ַ���������ȷ˳��
	return result;  // return BigInt(result);  ��BigInt(string)���죬�������Զ�ת��
}

// ��������
BigInt operator-(const BigInt& lhs, const BigInt& rhs)
{
	/*
	* �Ҵ���ַ����������С���󱻼���
	* ���������ַ�������������λ��bool flag��,string result������
	*/
	string result;
	bool flag = false;
	bool minor = false;

	string maxStr = lhs.strDigit;
	string minStr = rhs.strDigit;
	if (maxStr.length() < minStr.length())
	{
		maxStr = rhs.strDigit;
		minStr = lhs.strDigit;
		minor = true;
	}
	else if (maxStr.length() == minStr.length())
	{
		if (maxStr < minStr)
		{
			maxStr = rhs.strDigit;
			minStr = lhs.strDigit;
			minor = true;
		}
		else if (maxStr == minStr)
		{
			return string("0");
		}
	}

	int i = maxStr.length() - 1;
	int j = minStr.length() - 1;
	for (;i >= 0 && j >= 0;--i, --j)
	{
		int ret = maxStr[i] - minStr[j];
		if (flag)
		{
			ret -= 1;
			flag = false;
		}

		if (ret < 0)
		{
			ret += 10;
			flag = true;
		}
		result.push_back(ret + '0');
	}

	while (i >= 0)  // ���ݹ�������ѭ��������j��������>0��ֻ��i����
	{
		int ret = maxStr[i] - '0';
		if (flag)
		{
			ret -= 1;
			flag = false;
		}

		if (ret < 0)
		{
			ret += 10;
			flag = true;
		}
		result.push_back(ret + '0');
		i--;
	}

	// ȥ����λ�����0
	string retStr;
	auto it = result.rbegin();
	for (;it != result.rend();++it)
	{
		if (*it != '0')
		{
			break;
		}
	}
	for (;it != result.rend(); ++it)
	{
		retStr.push_back(*it);
	}

	if (minor)  // �Ƿ��Ǹ���
	{
		retStr.insert(retStr.begin(), '-');
	}

	//reverse(result.begin(), result.end());

	return retStr;
}

int main()
{
	BigInt int1("14572154415842154");
	BigInt int2("84579363586655858358784556556");
	cout << int1 + int2 << endl;
	cout << int1 - int2 << endl;

	BigInt int3("999545");
	BigInt int4("999544");
	cout << int3 - int4 << endl;

	BigInt int5("123");
	BigInt int6("99");
	cout << int6 - int5 << endl;
	return 0;
}
#endif