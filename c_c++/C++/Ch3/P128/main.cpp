#include <iostream>

using namespace std;

class Circle
{
private:
    int radius;

public:
    Circle();
    Circle(int r);
    int getRadius();
    void setRadius(int r);
    double getArea();
};
Circle::Circle()
{
    radius = 1;
}
Circle::Circle(int r)
{
    radius = r;
}
void Circle::setRadius(int r)
{
    radius = r;
}
int Circle::getRadius()
{
    return radius;
}
double Circle::getArea()
{
    return radius * radius * 3.14;
}

// 그림 3-17 멤버를 public으로 선언하면 보호 받지 못함(b)
int main()
{
    Circle waffle(5); // 생성자에서 radius  설정
    // waffle.radius = 5; // private 멤버 접근 불가
    waffle.setRadius(10); // setter함수로 radius 설정
    // cout << "waffle.radius : " << waffle.radius << endl; // private 멤버 접근 불가
    cout << "waffle.radius : " << waffle.getRadius() << endl; // getter함수로 멤버 값 받아오기
    cout << "getArea : " << waffle.getArea() << endl;

    return 0;
}