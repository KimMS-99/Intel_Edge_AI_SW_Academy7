#include <iostream>

using namespace std;

class Circle
{
    int radius;

public:
    Circle() { radius = 1; }
    Circle(int radius) { this->radius = radius; }
    void setRadius(int radius) { this->radius = radius; }
    double getArea() { return 3.14 * radius * radius; }
};

// 예제 5-4 객체에 대한 참조
int main()
{
    Circle circle;
    Circle &refc = circle; // circle 객체에 대한 참조 변수 refc 선언
    refc.setRadius(10);
    cout << refc.getArea() << " " << circle.getArea() << endl;

    cout << &circle << " " << &refc << endl; // 동일한 주소를 가르킴
}