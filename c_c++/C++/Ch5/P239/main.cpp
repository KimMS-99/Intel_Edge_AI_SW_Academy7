#include <iostream>
#include "circle.h"

void increaseCircle(Circle &c) // c는 참조 매개 변수
{
    int r = c.getRadius();
    c.setRadius(r + 1); // c가 참조하는 원본 객체의 반지름 1 증가
}

// 예제 5-6 참조에 의한 호출로 Circle 객체에 참조 전달
int main()
{
    Circle waffle(30);
    increaseCircle(waffle); // 참조에 의한 호출
    cout << waffle.getRadius() << endl;
}