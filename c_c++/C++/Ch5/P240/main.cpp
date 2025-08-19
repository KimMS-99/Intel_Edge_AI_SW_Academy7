#include <iostream>
#include "circle.h"

void readRadius(Circle &c)
{
    int n;
    cout << "정수 값으로 반지름을 입력하세여>> ";
    cin >> n;
    c.setRadius(n);
}

// 예제 5-7 참조 매개 변수를 가진 함수 만들기
int main()
{
    Circle donut;
    readRadius(donut);
    cout << "donut의 면적 = " << donut.getArea() << endl;
}