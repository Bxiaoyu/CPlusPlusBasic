#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
* 编程题目：请实现以下类方法，完成大数加法
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
	string strDigit;  // 使用字符串存储大整数
};

ostream& operator<<(ostream& out, const BigInt& src)
{
	out << src.strDigit;
	return out;
}

// 大数加法
BigInt operator+(const BigInt& lhs, const BigInt& rhs)
{
	/*
	* 遍历字符串l,r，从后往前遍历
	* 同位置的数字相加，进位flag 存入一个结果当中 string result
	* 同时完成
	* 某个字符串先完成，都要考虑进位
	*/
	string result;
	bool flag = false;
	int i = lhs.strDigit.length() - 1;
	int j = rhs.strDigit.length() - 1;

	for (;i >= 0 && j >= 0; --i, --j)
	{
		/*
		* 在ASCII编码中，字符实际上对应一个数字。例如，字符'0'的ASCII值是48，字符'1'的ASCII值是49，依此类推。
		* 你可以通过减去'0'的ASCII值来得到一个数字。
		*/
		int ret = lhs.strDigit[i] - '0' + rhs.strDigit[j] - '0';
		if (flag)
		{
			ret += 1;
			flag = false;
		}

		if (ret >= 10)
		{
			ret %= 10;  // 取余数
			flag = true;
		}

		result.push_back(ret + '0');
	}

	// 判断 i,j 是否还大于0
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

	reverse(result.begin(), result.end());  // 反转字符串才是正确顺序
	return result;  // return BigInt(result);  有BigInt(string)构造，编译器自动转换
}

// 大数减法
BigInt operator-(const BigInt& lhs, const BigInt& rhs)
{
	/*
	* 找大的字符串左减数，小的左被减数
	* 遍历两个字符串，减法，借位（bool flag）,string result存下来
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

	while (i >= 0)  // 根据规则上面循环结束，j不可能再>0，只有i可能
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

	// 去除高位多余的0
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

	if (minor)  // 是否是负数
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