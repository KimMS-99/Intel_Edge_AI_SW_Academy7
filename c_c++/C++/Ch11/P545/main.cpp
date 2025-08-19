#include <iostream>
using namespace std;

void get1()
{
	cout << "cin.get()로 <Enter> 키까지 입력 받고 출력합니다>>";
	int ch; // EOF와의 비교를 위해 int 타입으로 선언
	while ((ch = cin.get()) != EOF)
	{				  // 문자 읽기
		cout.put(ch); // 읽은 문자 출력
		if (ch == '\n')
			break; // <Enter> 키가 입력되면 읽기 중단
	}
}

void get2()
{
	cout << "cin.get(char&)로 <Enter> 키까지 입력 받고 출력합니다>>";
	char ch;
	while (true)
	{
		cin.get(ch); // 문자 읽기
		if (cin.eof())
			break;	  // EOF를 만나면 읽기 종료
		cout.put(ch); // ch의 문자 출력
		if (ch == '\n')
			break; // <Enter> 키가 입력되면 읽기 중단
	}
}

// 예제 11-2 get()과 get(char&)을 이용한 한 줄의 문자 읽기
int main()
{
	get1(); // cin.get()을 이용하는 사례
	get2(); // cin.get(char&)을 이용하는 사례
}