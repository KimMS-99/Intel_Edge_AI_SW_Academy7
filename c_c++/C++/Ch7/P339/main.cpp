#include <iostream>
#include "power.h"

// 예제 7-6 두 개의 Power 객체를 더하는 += 연산자 작성
int main()
{
	Power a(3, 5), b(4, 6), c;
	a.show();
	b.show();
	c = a += b; // 파워 객체 더하기
	a.show();
	c.show();
}