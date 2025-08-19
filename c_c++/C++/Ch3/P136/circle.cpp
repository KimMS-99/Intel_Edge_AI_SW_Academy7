#include <iostream>
#include "circle.h"

using namespace std;

Circle::Circle()
{
    radius = 1;
    cout << "반지름 : " << radius << " 원 생성" << endl;
}
Circle::Circle(int r)
{
    radius = r;
    cout << "반지름 : " << radius << " 원 생성" << endl;
}
Circle::~Circle()
{
    cout << "반지름 : " << radius << " 원 소멸" << endl;
}
double Circle::getArea()
{
    return 3.14 * radius * radius;
}

Circle globalDonut(1000);
Circle globalPizza(2000);

void f() // 함수 실행되고 함수 종료될때 각각 생성자 소멸자
{
    Circle fDonut(100);
    Circle fPizza(200);
}