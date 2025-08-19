#include <iostream>
using namespace std;

// 원형 선언
void f(char c = ' ', int line = 1);

// 함수 구현
void f(char c, int line)
{
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << c;
		cout << endl;
	}
}

// 예제 6-4 디폴트 매개 변수를 가진 함수 만들기 연습
int main()
{
	f();	   // 한 줄에 빈칸을 10개 출력한다.
	f('%');	   // 한 줄에 '%'를 10개 출력한다.
	f('@', 5); // 다섯 줄에 '@'를 10개 출력한다.
}