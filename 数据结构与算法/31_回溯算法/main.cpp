#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
* �����㷨˼��
*/

/*
* ��ռ�-�Ӽ���
*/

#if 0
void func(int arr[], int i, int length, int x[])
{
	if (i == length)  // �ݹ��������
	{
		for (int j = 0; j < length; j++)
		{
			if(x[j] == 1)
				cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		x[i] = 1;  // ѡ��i�ڵ�
		func(arr, i + 1, length, x);  // ����i������
		x[i] = 0;  // ��ѡ��i�ڵ�
		func(arr, i + 1, length, x);  // ����i���Һ���
	}
}

int main()
{
	int arr[] = { 1,2,3 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int x[3] = { 0 };
	func(arr, 0, length, x);
	return 0;
}
#endif

#if 0
/*
* ����ѡ�����⣺����һ�����飬����������һ����������������֮����ʣ�µ�����֮�͵Ĳ���С
*/
int arr[7] = { 12,6,7,11,16,3,8 };
//const int length = sizeof(arr) / sizeof(arr[0]);
const int length = 7;
int x[7] = { 0 };  // �Ӽ����������飬��¼�ڵ��������ӻ����Һ��ӡ�����i�ڵ㱻ѡ��&δ��ѡ��
int bestx[7] = { 0 };  // ��¼���Ž�
unsigned int minNum = 0xFFFFFFFF;  // ��¼��С�Ĳ�ֵ
int sum = 0;  // ��¼��ѡ�Ӽ����ֵ��ܺ�
int r = 0;  // ��¼δѡ�����ֵĺ�

// �����Ӽ���
void func(int i)
{
	if (i == length)
	{
		int result = abs(sum - r);
		if (result < minNum)
		{
			minNum = result;
			// ��Ҫ��¼һ�²�ֵ��С���Ӽ�
			for (int j = 0; j < length; j++)
			{
				bestx[j] = x[j];
			}
		}
	}
	else
	{
		r -= arr[i];
		sum += arr[i];
		x[i] = 1;
		func(i + 1);  // ѡ��i�ڵ�
		sum -= arr[i];
		r += arr[i];

		x[i] = 0;
		func(i + 1);  // ��ѡ��i�ڵ�
	}
}

int main()
{
	for (int v : arr)
	{
		r += v;
	}

	func(0);

	for (int i = 0; i < length; i++)
	{
		if (bestx[i] == 1)
		{
			cout << arr[i] << " ";
		}
	}
	cout << endl;
	cout << "min:" << minNum << endl;

	return 0;
}
#endif

#if 0
/*
* ����ѡ�����⣺����2n������������������n������������������֮����ʣ�µ�����֮�͵Ĳ���С
*/
vector<int> arr = { 12,6,7,11,16,3,8,9 };
int length = arr.size();
vector<int> x;      // ��¼�Ӽ���ѡ���Ԫ��
vector<int> bestx;  // ��¼���Ž�
int sum = 0;        // ��¼�Ӽ�����ѡ���ֵĺ�
int r = 0;          // ��¼δѡ�����ֵĺ�
unsigned int minNum = 0xFFFFFFFF;  // ��¼��С��ֵ
int cnt = 0;        // ��¼�������Ӽ����������ڲ���
int leftcnt = length;  // ��¼δ��������ֵĸ���

void func(int i)
{
	if (i == length)
	{
		// �õ��Ӽ�����һ���⣬��Ӧһ��Ҷ�ӽڵ�
		cnt++;
		if (x.size() != length / 2)
		{
			return;
		}

		int result = abs(sum - r);
		if (result < minNum)
		{
			minNum = result;
			bestx = x;
		}
	}
	else
	{
		leftcnt--;
		if (x.size() < length / 2)  // ������֦������㷨Ч�ʣ�ѡ�����ֵ�ǰ�᣺��δѡ��n������
		{
			sum += arr[i];
			r -= arr[i];
			x.push_back(arr[i]);
			func(i + 1);  // ����i�����ӣ���ʾѡ��i��λԪ��
			sum -= arr[i];
			r += arr[i];
			x.pop_back();
		}

		// ��������֦�ܲ��ܼ��أ���ѡ�����ֵĸ��� + δ����ѡ����������ֵĸ���(i+1,i+2...n) >= n��Ԫ��
		if(x.size() + leftcnt >= length / 2)
			func(i + 1);  // ����i���Һ��ӣ���ʾ��ѡ��i��λԪ��

		// ��ǰi�ڵ��Ѵ����꣬���ݵ��丸�ڵ�
		leftcnt++;
	}
}

int main()
{
	for (int v : arr)
	{
		r += v;
	}

	func(0);

	for (int v : bestx)
	{
		cout << v << " ";
	}
	cout << endl;
	cout << "min: " << minNum << endl;
	cout << "cnt: " << cnt << endl;
	return 0;
}
#endif

/*
* ��ѡ���֣���һ������������ѡ��һ�����֣������ǵĺ͵���ָ����ֵ�����ڴ�ӡ�������ڴ�ӡ
*/
#if 0
int arr[] = { 4,8,12, 16,7,3,9 };
const int length = sizeof(arr) / sizeof(arr[0]);
int target = 18;
vector<int> x;   // ��¼ѡ�������
int sum = 0;     // ��¼��ѡ���ֵĺ�
int r = 0;       // ��¼δ�������ֵ��ܺ�

void func(int i)
{
	if (i == length)
	{
		if (sum != target)
		{
			return;
		}
		
		for (int v : x)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		r -= arr[i];  // ����ǰi�ڵ�
		if (sum + arr[i] <= target)  // ������֦  ��ѡ�����ֵĺ� + ����Ҫѡ�������
		{
			x.push_back(arr[i]);
			sum += arr[i];
			func(i + 1);
			x.pop_back();
			sum -= arr[i];
		}

		if (sum + r >= target)  // ������֦  ��ѡ�����ֵĺ� + ʣ��Ŀ��Ա�ѡ������ֵĺͣ�i+1, i+2...n��
		{
			func(i + 1);
		}
		r += arr[i];
	}
}

int main()
{
	for (int v : arr)
	{
		r += v;
	}

	func(0);

	return 0;
}
#endif
#if 0
// ����Ч��д����N����
int arr[] = { 4,8,12, 16,7,3,9,3 };
const int length = sizeof(arr) / sizeof(arr[0]);
int target = 18;
vector<int> vec;   // ��¼ѡ�������

void func(int i, int number)
{
	if (number == 0)
	{
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}
	else
	{
		// �Ե�ǰ�ڵ㿪ʼ����ʣ��Ԫ�صĺ��ӽڵ�����
		for (int k = i; k < length; ++k)
		{
			if (number >= arr[k])  // ʣ�´�ѡԪ��ҪС��number
			{
				vec.push_back(arr[k]);
				// ��ǰ���������һ��ʱ arr[k] != arr[k-1]
				// ������ѡ���ظ�Ԫ��
				func(k + 1, number - arr[k]);  // �������ӽڵ㣬arr[k]�ĺ��ӽڵ�
				// ����ѡ���ظ�Ԫ��
				//func(k, number - arr[k]);
				vec.pop_back();
			}
		}
	}
}

int main()
{
	func(0, target);
	return 0;
}
#endif

/*
* 0-1�������⣺��һ����Ʒ���������ֱ�Ϊ��w1,w2,w3...wn�����ֵ�ֱ�Ϊ��v1,v2,v3...vn��������һ��������������λC,
* ����ô����Ʒװ�뱳�����ܹ�ʹ�����ļ�ֵ��󻯣�
*/
#if 0
int w[] = { 12,5,8,9,6 };  // ��Ʒ����
int v[] = { 9,11,4,7,8 };  // ��Ʒ��ֵ
const int length = sizeof(w) / sizeof(w[0]);
vector<int> x;  // ѡ�����Ʒ
vector<int> bestx;  // ��¼����ѡ�����Ʒ
int c = 20;     // ����������
int cw = 0;     // ��ѡ����Ʒ������
int cv = 0;     // ��ѡ����Ʒ�ļ�ֵ
int maxV = 0;   // ��¼װ�뱳������Ʒ������ֵ
int r = 0;      // δ������Ʒ���ܼ�ֵ

void func(int i)
{
	if (i == length)
	{
		if (maxV < cv)
		{
			maxV = cv;
			bestx = x;
		}
	}
	else
	{
		r -= v[i];
		if (cw + w[i] <= c)  // ��ѡ����Ʒ������ + ����ѡ�����Ʒ������
		{
			x.push_back(w[i]);
			cw += w[i];
			cv += v[i];
			func(i + 1);
			x.pop_back();
			cw -= w[i];
			cv -= v[i];
		}

		// maxV cv + [i+1...n]�ܼ�ֵ > maxV
		if (cv + r > maxV)
		{
			func(i + 1);
		}
		r += v[i];
	}
}

int main()
{
	for (int val : v)
	{
		r += val;
	}

	func(0);

	for (int w : bestx)
	{
		cout << w << " ";
	}
	cout << endl;
	cout << "maxV:" << maxV << endl;
	return 0;
}
#endif

/*
* ��ռ�-����������ģ��
*/
#if 0
void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void func(int arr[], int i, int length)
{
	if (i == length)
	{
		for (int j = 0; j < length; ++j)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		// ����i�ڵ�����к��ӽڵ�
		for (int k = i; k < length; ++k)
		{
			swap(arr, i, k);
			func(arr, i + 1, length);
			swap(arr, i, k);  // һ��Ҫ�ٽ�������
		}
	}
}

int main()
{
	int arr[] = { 1,2,3,4 };
	int length = sizeof(arr) / sizeof(arr[0]);
	func(arr, 0, length);

	return 0;
}
#endif

/*
* ����������˻ʺ�����
*/
int cnt = 0;  // ͳ����������

void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

bool judge(int arr[], int i)  // i��ʾ��ǰ���ûʺ����ӵ�λ��
{
	for (int j = 0; j < i; ++j)
	{
		if (i == j || arr[i] == arr[j] || abs(i-j) == abs(arr[i] - arr[j]))
		{
			return false;
		}
	}

	return true;
}

void func(int arr[], int i, int length)
{
	if (i == length)
	{
		cnt++;
		for (int j = 0; j < length; ++j)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i; k < length; ++k)
		{
			swap(arr, i, k);
			if(judge(arr, i))  // �жϵ�i��λ�õ�Ԫ���Ƿ���ϰ˻ʺ������
				func(arr, i+1, length);  // ���ɺ��ӽڵ㣬��һϵ�����з�ʽ
			swap(arr, i, k);
		}
	}
}

int main()
{
	// ��arr���±굱���У��±��Ӧ��Ԫ��ֵ������
	int arr[] = { 1,2,3,4,5,6,7,8 };
	int n = 8;
	func(arr, 0, n);
	cout << "�ܹ�: " << cnt << " ��." << endl;
	return 0;
}