#include <iostream>
#include "circle.h"

// 예제 4-2 Circle 클래스의 배열 선언 및 활용
int main()
{
    Circle circleArray[3]; // Circle 객체 배열 생성

    // 배열의 각 원소 객체의 멤버 접근
    // circleArray[0].setRadius(10);
    // circleArray[1].setRadius(20);
    // circleArray[2].setRadius(30);
    int num[3] = {10, 20, 30};
    for (int i = 0; i < 3; i++)
        circleArray[i].setRadius(num[i]);

    for (int i = 0; i < 3; i++) // 배열의 각 원소 객체의 멤버 접근
        cout << "Circle" << i << "의 면적은 " << circleArray[i].getArea() << endl;

    Circle *p;
    p = circleArray;            // 배열의 첫 번째 원소의 주소를 p의 저장
    for (int i = 0; i < 3; i++) // 객체 포인터로 배열 접근
    {
        cout << "Circle " << i << "의 면적은" << p->getArea() << endl;
        p++; // 배열의 다음 원소를 가리킴
    }
}