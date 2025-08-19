#include <iostream>
#include "power.h"

// 예제 7-7 b = a + 2;의 + 연산자 작성
int main()
{
	Power a(3, 5), b;
	a.show();
	b.show();
	b = a + 2; // 파워 객체와 정수 더하기
	a.show();
	b.show();
}