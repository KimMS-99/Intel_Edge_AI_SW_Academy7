#include <iostream>
#include "circle.h"

Circle getCircle()
{
    Circle tmp(30);
    return tmp; // 객체 tmp을 리턴한다
}

// 예제 5-2 객체 리턴
int main()
{
    Circle c; // 객체가 생성된다. radius=1로 초기화된다.
    cout << c.getArea() << endl;
    c = getCircle(); // tmp 객체가 c에 복사된다, c의 radius는 30이 된다.
    cout << c.getArea() << endl;
}