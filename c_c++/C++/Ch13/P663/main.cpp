#include <iostream>
#include <string>
using namespace std;

class MyException
{ // 사용자가 만드는 기본 예외 클래스 선언
	int lineNo;
	string func, msg;

public:
	MyException(int n, string f, string m)
	{
		lineNo = n;
		func = f;
		msg = m;
	}
	void print() { cout << func << ":" << lineNo << ", " << msg << endl; }
};

class DivideByZeroException : public MyException
{ // 0으로 나누는 예외 클래스 선언
public:
	DivideByZeroException(int lineNo, string func, string msg)
		: MyException(lineNo, func, msg) {}
};

class InvalidInputException : public MyException
{ // 잘못된 입력 예외 클래스 선언
public:
	InvalidInputException(int lineNo, string func, string msg)
		: MyException(lineNo, func, msg) {}
};

// 예제 13-8 예외 클래스 만들기
int main()
{
	int x, y;
	try
	{
		cout << "나눗셈을 합니다. 두 개의 양의 정수를 입력하세요>>";
		cin >> x >> y;
		if (x < 0 || y < 0)
			throw InvalidInputException(33, "main()", "음수 입력 예외 발생"); // 임시 객체 생성
		if (y == 0)
			throw DivideByZeroException(35, "main()", "0으로 나누는 예외 발생"); // 임시 객체 생성
		cout << (double)x / (double)y;
	}
	catch (DivideByZeroException &e)
	{
		e.print();
	}
	catch (InvalidInputException &e)
	{
		e.print();
	}
}