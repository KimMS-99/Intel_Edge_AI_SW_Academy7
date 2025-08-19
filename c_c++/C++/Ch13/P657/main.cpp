#include <iostream>
#include <cstring>
using namespace std;

// 문자열을 정수로 변환하여 리턴
// 정수로 변환하기 어려운 문자열의 경우, char* 타입 예외 발생
int stringToInt(const char x[])
{
	int sum = 0;
	int len = strlen(x);
	for (int i = 0; i < len; i++)
	{
		if (x[i] >= '0' && x[i] <= '9')
			sum = sum * 10 + x[i] - '0';
		else
			throw x; // char* 타입의 예외 발생
	}
	return sum;
}

// 예제 13-6 문자열을 정수로 변환하기
int main()
{
	int n;
	try
	{
		n = stringToInt("123"); // 문자열을 정수로 변환
		cout << "\"123\" 은 정수 " << n << "로 변환됨" << endl;
		n = stringToInt("1A3"); // 문자열을 정수로 변환
		cout << "\"1A3\" 은 정수 " << n << "로 변환됨" << endl;
	}
	catch (const char *s)
	{
		cout << s << " 처리에서 예외 발생!!" << endl;
		return 0; // 프로그램 종료
	}
}