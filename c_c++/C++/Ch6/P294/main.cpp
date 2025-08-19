#include <iostream>
using namespace std;

int add(int a, int b)
{
	return a + b;
}

int add(int a, int &b)
{
	b = b + a;
	return b;
}

// 예제 6-8 참조 매개 변수로 인한 함수 중복의 모호성
int main()
{
	int s = 10, t = 20;
	cout << add(s, t); // 컴파일 오류
}
