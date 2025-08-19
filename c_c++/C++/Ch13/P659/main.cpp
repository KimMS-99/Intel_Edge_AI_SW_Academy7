#include <iostream>
#include "MyStack.h"

using namespace std;

// 예제 13-7 예외 처리를 가진 스택 클래스 만들기 - 스택 클래스의 완전판
int main()
{
	MyStack intStack;
	try
	{
		intStack.push(100);
		intStack.push(200);
		cout << intStack.pop() << endl;
		cout << intStack.pop() << endl;
		cout << intStack.pop() << endl;
	}
	catch (const char *s)
	{
		cout << "예외 발생 : " << s << endl;
	}
}