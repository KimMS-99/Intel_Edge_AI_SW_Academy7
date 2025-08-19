#include <iostream>
#include "power.h"

// 예제 7-5 두 개의 Power 객체를 비교하는 == 연산자 작성
int main()
{
	Power a(3, 5), b(3, 5); // 2 개의 동일한 파워 객체 생성
	a.show();
	b.show();
	if (a == b)
		cout << "두 파워가 같다." << endl;
	else
		cout << "두 파워가 같지 않다." << endl;
}