#include <iostream>
#include "circle.h"

using namespace std;

template <class T>
void myswap(T &a, T &b)
{
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
}

// 예제 10-1 제네릭 myswap() 함수 만들기
int main()
{
    int a = 4, b = 5;
    myswap(a, b);
    cout << "a = " << a << ", b = " << b << endl;

    double c = 0.3, d = 12.5;
    myswap(c, d);
    cout << "c = " << c << ", d = " << d << endl;

    Circle donut(5), pizza(20);
    myswap(donut, pizza);
    cout << "donut = " << donut.getRadius() << ", pizza = " << pizza.getRadius() << endl;
}