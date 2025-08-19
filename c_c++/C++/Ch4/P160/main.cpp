#include <iostream>
#include "circle.h"

using namespace std;

// 예제 4-1 객체 포인터 선언 및 활용
int main()
{
    Circle donut;
    Circle pizza(30);

    // 객체 이름으로 멤버 접근
    cout << donut.getArea() << endl;

    // 객체 포인터로 멤버 접근
    Circle *p;

    p = &donut;

    cout << "p의 포인터 : " << p << endl; // 포인터 출력
    cout << "donut 의 주소 : " << &donut << endl;
    cout << p->getArea() << endl;   // donut의 getArea() 호출
    cout << (*p).getArea() << endl; // donut의 getArea() 호출

    p = &pizza;
    cout << "p의 포인터 : " << p << endl; // 포인터 출력
    cout << "pizza 의 주소 : " << &pizza << endl;
    cout << p->getArea() << endl;   // donut의 getArea() 호출
    cout << (*p).getArea() << endl; // donut의 getArea() 호출
}