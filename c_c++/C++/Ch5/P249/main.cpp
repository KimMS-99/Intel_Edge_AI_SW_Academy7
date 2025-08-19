#include <iostream>
#include "circle.h"

// 예제 5-9 Circle 클래스의 복사 생성자와 객체 복사
int main()
{
    // Circle test;
    Circle src(30);   // src 객체의 보통 생성자 호출
    Circle dest(src); // dest 객체의 복사 생성자 호출
    cout << "원본의 면적 = " << src.getArea() << endl;
    cout << "사본의 면적 = " << dest.getArea() << endl;
}